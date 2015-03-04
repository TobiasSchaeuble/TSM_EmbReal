//-----------------------------
//Rules 
// shows simple makefile rules graphically using graphviz
//(c) H.Buchmann FHNW 2012
//$Id$
//input rules generated by gcc -MM
//rules from stdin
//-----------------------------
import java.util.Vector;
import java.util.Map;
import java.util.TreeMap;
import java.io.InputStreamReader;
import java.io.StringWriter;
class Rules
{
//TODO better removal of the prefixes
 private Map<String,Rule> rules=new TreeMap<String,Rule>();
 
 private static String quote(String s){return "\""+s+"\"";}
 
 private static String name(String s)
 {
  return s.replaceAll("\\..*$","");
 }
 
 class Graph
 {
  private Map<String,Node> graph=new TreeMap<String,Node>();
  
  void add(String rule) //the target of a Rule
  {
   String name=name(rule);
   Rule r=rules.get(name);
   if (r==null) 
      {
       System.err.println("no rule '"+name+"'");
       return; 
      }
   node(name);
  }
  
  Node node(String id)
  {
   Node nd=graph.get(id);
   if (nd==null)
      {
       nd=new Node(id);
       graph.put(id,nd);
      }
   return nd;
  }
 
  class Node
  {
   String id;
   Vector<Node> children=new Vector<Node>();
   
   void children(Rule r)
   {
    for(String p:r.prerequisites)
    {
     String n=name(p);
     if (!n.equals(id)) 
        {
	 Node ch=node(name(p));
	 children.add(ch);
	}
    }
   }
   
   Node(String id) 
   {
    this.id=id;
    Rule r=rules.get(id);
    if (r!=null) children(r);
   }
   
   void show()
   {
    System.out.print(quote(id)+"->{");
    for(Node n:children) System.out.print(quote(n.id)+" ");
    System.out.println("};");
   }
  }
  
  void show()
  {
   System.out.println("digraph Modules {");
   for(Map.Entry<String,Node> e:graph.entrySet())
   {
    e.getValue().show();
   }
   System.out.println("}"); 
  }
  
  Graph()
  {
  }
  
 } //Graph
  
 class Rule
 {
  String          target;
  String          name; // suffix (.o) removed
  String[] prerequisites;
  
  Rule(String r)
  {
   String[] rr=r.split("\\s*:\\s*");
   target=rr[0];
   name=name(target);
   prerequisites=rr[1].split("\\s+");
   rules.put(name,this);
  }
  
  public String toString()
  {
   StringBuffer sb=new StringBuffer(target+":");
   for(String s:prerequisites) sb.append(" "+s);
   return sb.toString();
  }
  
  void makefile()
  {
   System.out.print(quote(target)+"->{");
   for(String s:prerequisites) System.out.print(quote(s)+" ");
   System.out.println("}");
  }
  
  void module()
  {
   System.out.print(quote(target)+"->{");
   for(String p:prerequisites)
   {
    if (!target.equals(p)) System.out.print(quote(p)+" ");
   }
   System.out.println("}");
  }
 } //Rule
  
 private static final String Prefix="(\\.\\./)+src/"; 

 private void makefile() 
 {
  System.out.println("digraph Rules {\n"+
                     "rankdir=LR;"
                    );
  for(Map.Entry<String,Rule> e:rules.entrySet())
  {
   e.getValue().makefile();  
  }
  System.out.println("}"); 
 }
 
 private void module()
 {
  Graph g=new Graph();
  for(Map.Entry<String,Rule> e:rules.entrySet())
  {
   g.add(e.getKey());
  }
  g.show();
 }
 
 Graph graph()
 {
  return new Graph();
 } 
 
 private void read() throws Exception
 {
  InputStreamReader src=new InputStreamReader(System.in);
  StringWriter      dst=new StringWriter();
  while(true)
  {
   int ch=src.read();
   if (ch<0) break;
   dst.write(ch);
  }
  dst.close();
  String[] rules=dst.toString().replaceAll("\\\\\\n"," ").replaceAll(Prefix,"").split("\\n+");
  for(String s:rules) 
  {
   new Rule(s);
  }
 }
 
 
 private Rules() throws Exception
 {
  read();
 }
 
 static private void usage()
 {
  System.err.println("usage Rules makefile|module [name]");
  System.exit(1);
 }
 
 public static void main(String args[]) throws Exception
 {
  if (args.length==0) usage();
  if (args[0].equals("makefile")) 
     {
      new Rules().makefile();
      return;
     }
  if (args[0].equals("module"))
     {
      Rules rules=new Rules();
      if (args.length==1) 
         {
	  rules.module();
	 }
         else
	 {
	  Graph g=rules.graph();
	  for(int i=1;i<args.length;++i)
	  {
	   g.add(args[i]);
	  }
	  g.show();
	 }
      return;	 
     }
     
  usage();
 }
}