#pragma once
/*------------------------
 defines for defining hw registers
 (c) H.Buchmann FHNW 2012
 $Id$
 see ARM docu
--------------------------*/
#define RW 
#define WO
#define RO const
#define VAR(name,offset,   type,reset) type unsigned name
#define ARR(name,start,end,type,reset) type unsigned name[1+(end-start)/sizeof(unsigned)]
