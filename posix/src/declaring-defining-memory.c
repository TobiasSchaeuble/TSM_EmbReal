/*--------------------
 declaring/defining memory
 (c) H.Buchmann FHNW 2009
 $Id$
 compile with gcc -std=c99
----------------------*/
typedef unsigned Type;          /* Type represents generic type */ 

typedef char TypeA;                  /* some more generic types */
typedef double TypeB;
typedef unsigned TypeC[3];                  /* an array as type */

                                                     /* structs */
typedef struct                 /* declaration of a struct pure C*/
{          /* members */
 Type  member; 
 TypeA memberA;
 TypeB memberB;
 TypeC memberC;
} AStruct;

struct BStruct            /* dedeclaration of a struct C++ like */
{
 Type  member; 
 TypeA memberA;
 TypeB memberB;
 TypeC memberC;
 AStruct memberD; 
};

/* global variable 
   - the unitialized variables are set to 0 bss section 
   - the initalized variables are in the data section 
*/
   
Type globalA;                        /* defined not initialized */
                                                  /* bss section*/ 
Type globalB=123;                    /* defined and initialized */
                                                /* data section */
#define SIZE (10)
Type arrayA[SIZE];         /* array not initialized bss section */
Type arrayB[SIZE]={10,9,8,7,6,5,4,3,1};
                              /* array initialized data section */

AStruct globalStructA;                   /* defined in bss all 0 */

                              /* defined and initialize in data */
struct BStruct globalStructB=
                       {1,                    /* member  */
                       'x',                   /* memberA */
		       3.1415,                /* memberB */
		       {1,2,3},               /* memberC */
                        
		       {2,'y',2.7182,{3,2,1}} /* memberD */
                        };


/* local variables (stack)
   - the unitialized variables have arbitrary values 
*/
 
void aFunction(Type parameter)
{
 Type localA;                        /* not initalized dangerous */
 Type localB=123;                                  /* initalized */
 Type localArrayA[SIZE];                /* array not initialized */
 Type localArrayB[SIZE]={10,20,30,40,50,60,70,80,90,100};
                                            /* array initialized */
 AStruct localStructA;                         /* not initalized */
 struct BStruct localStructB =                    /* initialized */
                       {1,                    /* member  */
                	'x',                   /* memberA */
			3.1415,                /* memberB */
			{1,2,3},               /* memberC */

			{2,'y',2.7182,{3,2,1}} /* memberD */
                        };
 
 localA=7; /* assign */
 /* this kind of loop compiles correctly with the -std=c99 switch */
 for(unsigned i=0;i<SIZE;++i) /* fill localArrayA */
 {
  localArrayA[i]=100-i;
 }
                            /* assign of members */
 localStructA=(AStruct){2,'u',1.001,{100,200,300}};
}
