//---------------------
//Memory: very didactic
//(c) H.Buchmann FHNW 2011
//$Id$
//TODO implements Memory for a 'file like' memory system
//     Address -> Name
//     Pattern -> bunch of bits
//---------------------
package mem;
public interface Memory<Address,Pattern> //see interface java.util.Map
                                         //semantically the same
					 //generic Address and Pattern 
{
//the basic operations
 public Pattern read(Address a);
 public void write(Address a,Pattern p);
}
