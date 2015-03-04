//-------------------------
//board
//(c) H.Buchmann FHNW 2014
//-------------------------
IMPLEMENTATION(sys_board,$Id$)
#include "sys/board.h"
#include "sys/deb/deb.h"
#include "sys/reg/pio.h"
#include "sys/reg/uart.h"
#include "sys/reg/wdt.h"
#include "sys/reg/pmc.h"
#include "sys/reg/eefc.h"
#include "sys/boot/big-bang-continued.h"
namespace sys
{
//see layout.ld
 extern "C" unsigned _data_beg[];
 extern "C" unsigned _data_end[];
 extern "C" unsigned _text_end[];
 extern "C" unsigned _bss_beg[];
 extern "C" unsigned _bss_end[];

 Board Board::board;

  
//TODO move it to SOC im a more generic form 
 void Board::pmc()
 {
  reg::EEFC0.FMR=(4<<8);
  reg::EEFC1.FMR=(4<<8);

  reg::PMC.CKGR_MOR=(0x37<<16) | //key
                    (0x08<< 8) | //MOSCXTST
		    (0x01<< 3) | //MOSCRCEN
		    (0x01<< 0) | //MOSCXTEN
		            0;

  while (!(reg::PMC.SR & (0x1<<0))) {}

 /* Switch to 3-20MHz Xtal oscillator */
  reg::PMC.CKGR_MOR = (0x37<<16) | //key
                      (0x08<< 8) | //MOSCXTST
	              (0x01<< 3) | //MOSCRCEN
		      (0x01<< 0) | //MOSCXTEN
		      (0x01<<24) | //MOSCSEL
		              0;

  while (!(reg::PMC.SR & (1<<16))) {}

  reg::PMC.MCKR = (reg::PMC.MCKR & ~0x3) | 
		        	  (1<<0) | //main clock
				      0;
  while (!(reg::PMC.SR & (1<<3))) {}

  /* Initialize PLLA */
  //mula      = 0xd    13
  //pllacount = 0x3f
  //diva      = 1   12 MHz * (mula+1)/diva = 12MHz * (13+1) /1 = 12MHz 14 = 168 MHz 
  reg::PMC.CKGR_PLLAR = (1<<29) |  //ONE
                      (0xd<<16) |  //mula
		      (0x1<< 0) |  //diva
		             0; 
  while (!(reg::PMC.SR &(1<<1))) {}

  /* Switch to main clock */
  reg::PMC.MCKR = (0x1<<4) | // prescale 2
        	  (0x1<<0) | // main clock
	        	0;
  while (!(reg::PMC.SR & (1<<3))) {}
  reg::PMC.MCKR = (0x1<<4) | //prescale 2
        	  (0x2<<0) | //PLLA
	        	0; 
  while (!(reg::PMC.SR & (1<<3))) {}
 }
 
 void Board::uart()
 {
//PA8 URXD Peripheral A
//PA9 UTXD Peripheral A
  static const unsigned PIN=(1<<8)|(1<<9);
  
  reg::PIOA.set(reg::PIO::PERIPH_A,PIN);

  reg::PMC.PCER0=(1<<8); //id uart = 8

  reg::UART.CR=(1<<2) | //RSTRX
               (1<<3) | //RSTTX
	       (1<<5) | //RXDIS
	       (1<<7) | //TXDIS
	       (1<<8) | //RSTSTA
		   0; 
  reg::UART.MR=(4<< 9) | //NO Parity
               (0<<14) | //normal mode
		    0;
  /*
   baudrate = MCK/(16*CD)
   CD       = MCK/(16*baudrate)
   
  */  
//  UART.BRGR=547; //9600 Baud
//  UART.BRGR=46;  //115200
   reg::UART.BRGR=MCK/(16*BAUDRATE);
 
  reg::UART.CR = (1<<6)| //TXEN
                 (1<<4)| //RXEN
                     0;
 }
 
 void Board::data()
 {
  unsigned* src=_text_end;
  for(unsigned* dst=_data_beg;dst!=_data_end;++dst)
  {
   *dst=*src++;
  }
 }
 
 void Board::bss()
 {
  for(unsigned*d=_bss_beg;d!=_bss_end;++d) *d=0;
 }
 
#define REG(r) \
deb::out(#r"\t");deb::hex((void*)&r);deb::out("\t");deb::hex(r);deb::newln()

 void Board::bigBang()
 {
  CortexM::cpsID_f();
  CortexM::cpsID_i();
  reg::WDT.MR=(1<<15); //disable watchdog
  pmc();
  deb::init();
  data();
  bss();
  uart();
  boot::start();
 }
 
 
 Board::Board()
 {
 }
}
