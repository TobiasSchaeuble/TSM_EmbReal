#pragma once
//-------------------------
//board
//(c) H.Buchmann FHNW 2014
//-------------------------
INTERFACE(sys_board,$Id$)
#include "sys/cortex-m.h"
#include "sys/soc.h"
namespace sys
{
 class Board:SOC
 {
  public:
   static const unsigned BAUDRATE=115200;
   static const unsigned MCK     =84000000;
   static void bigBang() __attribute__((noreturn));
   
  private:
   static Board board;
   static void pmc();                 //timing
   static void uart(); 
   static void data();
   static void bss();
   Board();
 };
}
