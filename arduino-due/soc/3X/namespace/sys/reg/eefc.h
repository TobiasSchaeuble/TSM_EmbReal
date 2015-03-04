#pragma once
//--------------------------------
//eefc Enhanced Embedded Flash Controller
//(c) H.Buchmann FHNW 2014
//--------------------------------
INTERFACE(sys_reg_eefc,$Id$)
namespace sys
{
 namespace reg
 {
  struct EEFC
  {
   enum Cmd
   {
    GETD  = 0x00,
    WP    = 0x01,
    WPL   = 0x02,
    EWP   = 0x03,
    EWPL  = 0x04,
    EA    = 0x05,
    SLB   = 0x08,
    CLB   = 0x09,
    GLB   = 0x0A,
    SGPB  = 0x0B,
    CGPB  = 0x0C,
    GGPB  = 0x0D,
    STUI  = 0x0E,
    SPUI  = 0x0F,
    GCALB = 0x10    
   };
   
   unsigned FMR; //0x00 Flash Mode Register
   unsigned FCR; //0x04 Flash Command Register
   unsigned FSR; //0x08 Flash Status Register
   unsigned FRR; //0x0c Flash Result Register

  };
  extern volatile EEFC EEFC0;
  extern volatile EEFC EEFC1;
 }
}


