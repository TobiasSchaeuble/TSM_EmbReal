//--------------------------
//cpu-demo
//(c) H.Buchmann FHNW 2015
//--------------------------
IMPLEMENTATION(test_cpu_demo,$Id$)
#include "sys/msg.h"
class Demo
{
 static Demo demo; //declaration instance of Demo
 Demo();           //constuctor
 
//implemented in assembler 
 static unsigned op(unsigned x,unsigned y);
 static void copy(unsigned&dst,unsigned& src);
 static void swap(unsigned&x,  unsigned& y);
};

Demo Demo::demo;  //instance of Demo
                  //constructor called

Demo::Demo()
{
 unsigned x=5;
 unsigned y=6;
 sys::msg<<"x="<<x<<" y="<<y<<"\n"
           "op("<<x<<","<<y<<")="<<op(x,y)<<"\n";
 swap(x,y);
 sys::msg<<"after swap: "<<x<<","<<y<<"\n";
 copy(x,y);
 sys::msg<<"after copy: "<<x<<","<<y<<"\n";
}
