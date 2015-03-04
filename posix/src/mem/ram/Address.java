//-----------------------
//Address
//(c) H.Buchmann FHNW 2011
//$Id$
// a linear address e.g. a number
//TODO:
// check for val>=0 
//-----------------------
package mem.ram;
class Address  //enclose simply an integer
{
 final int val;
 Address(int val)
 {
  this.val=val;
 }
}
