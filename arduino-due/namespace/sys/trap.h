#pragma once
INTERFACE(sys_trap,$Revision: 1.12 $)
//-----------------------
//trap
//implementation made in cpu/sys dir
//(c) H.Buchmann FHSO 2001
//$Id: trap.h 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//-----------------------
namespace sys
{
//--------------------------------------- Trap
 class Trap
 {
  public:
   virtual void onTrap()=0;
 };
}
