/*----------------------
  gic0
  (c) H.Buchmann FHNW 2013
 -----------------------*/
#include "sys/gic0.h"
onIRQ:
	sub lr, lr, #4
	push         {r0, r1, r2, r3, ip, lr}
	bl gic_onIRQ
	ldm     sp!, {r0, r1, r2, r3, ip, pc}^
