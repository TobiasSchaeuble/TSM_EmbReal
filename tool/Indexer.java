//---------------------
//Indexer
//(c) H.Buchmann FHNW 2011
//$Id$
//---------------------
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.LineNumberReader;
import java.io.File;
import java.io.InputStream;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.util.Vector;
import java.util.Stack;
import java.util.Map;
import java.util.TreeMap;
import java.util.Set;
import java.util.HashSet;
import java.util.Properties;
import java.util.Collections;
import java.util.Comparator;
import java.util.Set;
import java.util.TreeSet;
class Indexer
{
//TODO make a parameter
 private final Properties props=new Properties();
 
 private final String   idxHome;

 class Entry 
 {
  String          file;     //of file
  Vector<String>  lst;      //of file locations
  Map<String,Set<String>> slide=new TreeMap<String,           //name
                                               Set<String>>();//page nbr
  
  Entry(String file)
  {
   this.file=file;
   lst=locate(file);
  }
  
  void slide(String name,String page)
  {
   Set<String> pag=slide.get(name);
   if (pag==null)
      {
       pag=new TreeSet<String>();
       slide.put(name,pag);
      }
   pag.add(page);   
  }
  
  void showASCII()
  {
   System.out.print(file+": ");
   for(Map.Entry<String,Set<String>> e:slide.entrySet())
   {
    System.out.print(e.getKey()+"(");
    Set<String> pag=e.getValue();
    int i=0;
    for(String p:pag)
    {
     if (i>0) System.out.print(",");
     System.out.print(p);
     ++i;
    }
    System.out.print(") ");
   }
   System.out.println();
   for(String s:lst)
   {
    System.out.println("   "+s);
   }   
   System.out.println();
  }

  void showLatex()
  {
   System.out.println("\\begin{srcfileindex}{"+file+"}");
   for(Map.Entry<String,Set<String>> e:slide.entrySet())
   {
    System.out.print("\\textfile{"+e.getKey()+"}");
    System.out.print("{");
    Set<String> pag=e.getValue();
    int i=0;
    for(String p:pag)
    {
     if (i>0) System.out.print(",");
     System.out.print(p);
     ++i;
    }
    System.out.println("}");
   }
   System.out.println("\\begin{filelist}");
   if (lst.isEmpty()) System.out.println("  \\item -");
      else            for(String s:lst) System.out.println("  \\item "+s);
   System.out.println("\\end{filelist}");
   System.out.println("\\end{srcfileindex}");
  }  
 }

  
 private final String     srcHome;
 private Vector<String[]> fileList=new Vector<String[]>();
 private Set<String>      exclude =new HashSet<String>();


 private Map<String,Entry> index=new TreeMap<String,Entry>();
 
 private void insert(String slide, 
                     String file,
		     String page)

 {
  Entry e=index.get(file);
  if (e==null)
     {
      e=new Entry(file);
      index.put(file,e);
     }
  e.slide(slide,page);   
 }



 private void showASCII()
 {
  for(Map.Entry<String,Entry> e:index.entrySet())
  {
   e.getValue().showASCII();
  }
 }

 private void showLatex()
 {
  for(Map.Entry<String,Entry> e:index.entrySet())
  {
   e.getValue().showLatex();
  }
 }
 
 private void add(Stack<File> path,File f)
 {
//  System.out.println("add "+f);
  String[] p=new String[path.size()+2];
  int i=0;
  p[i++]=f.getName();
  int size=path.size();
  while(size>0)
  {
   p[i++]=path.get(--size).getName();
  }
  p[i]=null; //for terminating
  fileList.add(p);
 }
 
 private void fileList(Stack<File> path,File dir)
 {
//  System.err.println("fileList "+dir);
  File[] lst=dir.listFiles();
  for(File f:lst)
  {
//   System.err.println("  "+f.getName());
   if (f.isDirectory() && ! exclude.contains(f.getName())) 
      {
       path.push(f);
       fileList(path,f);
       path.pop();
       
      }
      else
      {
       add(path,f);
      }
  }
 }
 
 private void fileList()
 {
  Stack<File> path=new Stack<File>();
  fileList(path,new File(srcHome));
 }

 class Cmp implements Comparator<String[]>
 {
  public int compare(String[] ss0,String[] ss1) //reverse order
  {
   int i=0;
   while(true)
   {
    String s0=ss0[i];
    String s1=ss1[i];
    if (s0==null) return (s1==null)?0:1;
    if (s1==null) return (s0==null)?0:-1;
    int r=s0.compareTo(s1);
    if (r!=0) return -r;
    ++i;
   }
  }
  
  public boolean substring(String[] ss0,String ss1[])
  {
   int i=0;
   while(true)
   {
    String s0=ss0[i];
    String s1=ss1[i];
    if (s0==null) return true;
    if (s1==null) return false;
    if (s0.compareTo(s1)!=0) return false;
    ++i;
   }
  }
 }
 
 private Cmp cmp=new Cmp();
 
 private void sort()
 {
  Collections.sort(fileList,cmp);
 }

// typical entry
// \indexentry{hardware/access.c|hyperpage}{8}

 static private final Pattern Entry=
        Pattern.compile("\\\\indexentry\\{(.*?)(?:\\|hyperpage)?\\}\\{(.*)\\}");

 
 static private String[] revert(String f)
 {
  String[] ff=f.split("/+");
  int len=ff.length;
  String[] ffr=new String[len+1]; //last is null
  int i=0;
  while(len>0)
  {
   ffr[i++]=ff[--len];
  }
  ffr[i]=null;
  return ffr;
 }
 
 static String string(String[] ss) 
 {
  int len=ss.length-1;
  StringBuffer sb=new StringBuffer();
  while(len>0)
  {
   sb.append(ss[--len]);
   if (len>0) sb.append("/");
  }
  return sb.toString();
 }
 
 private int binarySearch(String[] s)
 {
//  System.out.println("binarySearch "+string(s));
  int i0=0;
  int i1=fileList.size();
  while((i1-i0)>1)
  {
   int im=(i0+i1)/2;
//   System.out.println(im+"\t"+string(fileList.get(im)));
   if (cmp.compare(s,fileList.get(im))<0)
      {
       i1=im;
      }
      else
      {
       i0=im;
      }
   
  }
  return i0;
 }
 
 private Vector<String> locate(String f)
 {
  String[] fr=revert(f);
  int i=binarySearch(fr);
  Vector<String> lst=new Vector<String>();
  while(true)
  {
   String[] ff=fileList.get(i--);
   if (cmp.substring(fr,ff))
      {
       lst.add(string(ff));
      }
      else break;
      
  }
  return lst;
 }

 private void index(String fil) throws Exception
 {
  String fName=idxHome+"/"+fil+".idx";
  try
  {
   LineNumberReader src=new LineNumberReader(new FileReader(fName));
   while(true)
   {
    String li=src.readLine();
    if (li==null) break;
    Matcher m=Entry.matcher(li);
    if (m.matches())
       {
        System.err.println(m.group(2)+  //page number
	                   "\t"+
	                   m.group(1)); //file name
	insert(fil,          //the slide
	       m.group(1),   //the file 
	       m.group(2));  //the page number
       }
   }
  }
  catch(FileNotFoundException ex)
  {
   System.err.println("File '"+fil+".idx' not found");
  }
 }
 
 private void index() throws Exception
 {
  for(String fil:props.getProperty("IDX_FILES").split("\\s+"))
  {
   index(fil);
  }
 }
 
 private void exclude()
 {
  for(String s:props.getProperty("EXCLUDE_DIR").split("\\s+"))
  {
   exclude.add(s);
  }
 }
 
 private Indexer(InputStream props) throws Exception
 {
  this.props.load(props);
  idxHome=this.props.getProperty("IDX_HOME");
  srcHome=this.props.getProperty("SRC_HOME");
  exclude();
  
  fileList();
  
  sort();
  
/*
  int i=0;
  for(String[] ss:fileList)
  {
   System.out.print((i++)+"\t");
   for(String s:ss) System.out.print(s+"/");
   System.out.println();
  }
*/
//  locate("big-bang-irq.S");
  index();
//  showASCII();
  showLatex();
 }
 
 public static void main(String args[]) throws Exception
 {
  new Indexer(System.in); 
 }
}
