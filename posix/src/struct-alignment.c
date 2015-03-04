/*-------------------- 
  struct-alignment.c
  (c) H.Buchmann FHNW 2009
  $Id$
  shows the use of define too
----------------------*/
#include <stdio.h>
#define PACKED

typedef struct
{
 unsigned memberA;
 char     memberB;
 unsigned memberC;
} 
#ifdef PACKED
__attribute__((packed))
#endif
AStruct; 


AStruct global={1,'2',10};

#define OFFSET(BASE,MEMBER) \
  (unsigned char*)(&BASE->MEMBER)-(unsigned char*)BASE
  
void show(AStruct* s)
{
 printf("Values\n"
        " memberA=%d\n"
	" memberB='%c'\n"
	" memberC=%x\n",
	s->memberA,
	s->memberB,
	s->memberC);
 printf("Offset in bytes\n"
        " memberA=%x\n"
	" memberB=%x\n"
	" memberC=%x\n",
	OFFSET(s,memberA),
	OFFSET(s,memberB),
	OFFSET(s,memberC)
	);
}

int main(int argc,char** args)
{
 show(&global);
 return 0;
}
