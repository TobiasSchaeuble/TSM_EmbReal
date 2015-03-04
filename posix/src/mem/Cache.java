//----------------------
//Cache
//(c) H.Buchmann FHNW 2011
//$Id$
//TODO implements Cache for a file like memory system
//     Address -> Name
//     Pattern -> bunch of bits
//----------------------
package mem;
public interface Cache<Address,Pattern> extends Memory<Address,Pattern>
		//cache is Memory 
{
 public boolean valid(Address a);
 public boolean hit(Address a);
 
}
