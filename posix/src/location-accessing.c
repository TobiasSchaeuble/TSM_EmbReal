/*----------------------
 location-accessing.c
 (c) H.Buchmann FHNW 2009
 $Id$
------------------------*/
#include <stdio.h>
typedef unsigned Type;          /* Type represents generic type */ 

Type global = 123;                   /* defined and initialized */ 

void simple_types_and_arrays()
{
 Type localarr[5];                                /* local array */
 global=5;                                   /* by value copying */
 Type* globalLocation=&global;                   /* & address of */
 *globalLocation=6;                              /* by reference */
 Type* localLocation=localarr;         /* localarr points to the */
                                    /* first element of localarr */
 /* accessing element 3 
   - 4 different cases accessing the same element */

 localarr[3]  =0x12345678;                 /* the typical syntax */
 *(localarr+3)=  0x123888;                        /* via pointer */
 *(3+localarr)=  0x999123; 
 3[localarr]  =0x87654321;                 /* not typical syntax */
 
 printf("global\n"
        "        value=%d\n"
        "     location=%p\n"
        "local\n"
	"     value[3]=%x\n"
	"  location[3]=%p\n",
       global,
       globalLocation,
       localarr[3],
       localarr+3); 
}

typedef char TypeA;                   /* some more generic types */
typedef char* TypeB;
typedef unsigned TypeC[3];                   /* an array as type */

typedef struct                 /* declaration of a struct pure C*/
{          /* members */
 Type  member; 
 TypeA memberA;
 TypeB memberB;
 TypeC memberC;
} AStruct;

AStruct globalS={5,'Y',"hello",{1,2,4}};

/* we use this function for showing the values of an AStruct */
/* call by reference */
void show(char* msg,AStruct* st) 
{
 printf(
  "%s\n"
  "  member =  %d (0x%x)\n"  /* number decimal/hexadecimal */
  "  memberA= '%c'\n"                              /* char */
  "  memberB= '%s'\n"                            /* string */
  "  memberC=  %d,%d,%d\n",
  msg,
  st->member,st->member,
  st->memberA,
  st->memberB,
  st->memberC[0],st->memberC[1],st->memberC[2]);
}

void structs_global()
{
 globalS.memberB="world";
}


void struct_by_value(AStruct v)
{
 v.member =0x12345678;
 v.memberB="by value";
 show("struct_by_value: local/parameter",&v);
}

void struct_by_reference(AStruct* v)
{
 v->member =0x87654321;
 v->memberB="by reference";
 show("struct_by_reference: local/parameter",v);
}

void structType()
{
 show("globalA",&globalS);
 struct_by_value(globalS); 
 show("globalB",&globalS);
 struct_by_reference(&globalS);
 show("globalC",&globalS);
}

int main(int argc,char** args)
{
// simple_types_and_arrays();
 structType();
 return 0; 
}
