/*---------------------
  gic0
  (c) H.Buchmann FHNW 2013
 ----------------------*/
#if __ASSEMBLER__ == 1
.global onIRQ
#else
#define ON_IRQ
extern void onIRQ();
#endif
 
