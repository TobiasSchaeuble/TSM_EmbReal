#pragma once
#ifndef __ASSEMBLER__ //dont include in assembler files
//--------------------------
//sys startup 
//(c) H.Buchmann FHSO 2003
//$Id: sys.h 13 2011-04-10 09:15:55Z hans.buchmann@ADM.DS.FHNW.CH $
//--------------------------
#ifndef __INCLUDE_LEVEL__
#define __INCLUDE_LEVEL__ 1
#endif

/*------------------------------------------------
 EARLY_INIT:
  init sequence derived at link time using tool nm
--------------------------------------------------*/

#ifndef EARLY_INIT
//(
//static __attribute((section(".text.startup"))) void  __text(){};

#ifdef __clang__
#define TEXT_STARTUP ".text.startup"
#elif defined __GNUC__
#define TEXT_STARTUP ".text.startup"
#endif



#define IMPLEMENTATION(name,info) \
static __attribute((section(TEXT_STARTUP))) void  __text(){};\
static sys::Mod __m  __attribute((section(".modules"),used,aligned(__SIZEOF_POINTER__)))={__FILE__,#info,&__text}; \
extern const sys::Mod*const name=&__m;\

#define INTERFACE(name,info) \
extern const sys::Mod*const  name; \
static const sys::Inc  __inc_##name __attribute__((section(".includes"),used,aligned(__SIZEOF_POINTER__)))={__INCLUDE_LEVEL__,&__m,&name};

#ifndef __GXX_EXPERIMENTAL_CXX0X__
#define static_assert(cond,msg)
#endif

namespace sys
{
 class Mod;

 struct Inc
 {
  const unsigned   includeLevel;
  const Mod*       mod;   //who includes
  const Mod*const* inc;
 };
 
 class Mod 
 {
  public:
   typedef void (*Global)();
   enum ErrorCode {OK,CONSTRUCTOR,DESTRUCTOR,CIRCULAR};

  private:
   struct Mod2  // the transient part of Mod 
   {
    const Mod*  m;
    const Inc*  inc; 
    unsigned    incN;
    Global      ctor;
    Global      dtor;
    bool        visited;
    bool        onStack; //for cirular import checking
    static void init(Mod2 nd[]);
    static void include(Mod2 nd[]); 
    unsigned sort(unsigned idx,Mod2 mod2[],Mod2* sorted[]);
    const char*const getName()const {return m->name+prefixSize;}

//------------------------------------------- debug 
    void showInclude() const;
    void show() const;
   };

   static const char*const ErrorCodeText[];
   static bool started;
   static ErrorCode errorCode; //0 means ok
   static unsigned prefixSize;

//------------------------------------------ instance methods   
   unsigned index() const;             //in module list
   
//------------------------------------------- debug 
//see SYS_SYS_DEBUG in implementation
   static void align(unsigned size,const char*const s,const char*const next); 
   static void showGlobal();
   static void showModules(const Mod2 nd[],unsigned len);
   static void showInclude(const Mod2 nd[],unsigned len);
   static void showStartup(const Mod2*const sorted[],unsigned len);
//------------------------------------------- debug end

   static void mkPrefix();
   static void matchGlobals(Mod2 mod[],unsigned len);
   static void sortModules(Mod2 m2[],Mod2* sorted[],unsigned len);
   static void call(Mod2* sorted[],unsigned len);
   static void thumbStart();
   
  public: 
//must be all public because no constructor can be used
   const char*const name;
   const char*const info;
   const Global text;
   const char* getName() const {return name+prefixSize;} 

//------------------------------------------ class methods
   static void start();
   static void stop();
   static ErrorCode getErrorCode();
   static const char* getErrorCodeText();
//------------------------------------------ access
   class Listener
   {
    public:
     virtual void onModule(const Mod*const,const Inc*const*,unsigned) const=0;
   };
   
   static void enumerate(const Listener&);
 }; //Mod
}
#else
//-----------------------------------------------------------
//)EARLY_INIT
#define IMPLEMENTATION(name,info) \
//extern const unsigned name __attribute__((used))=0;
//uncomment for include dependencies

#define INTERFACE(name,info) \
//extern const unsigned name; static const unsigned _##name=name;
//uncomment for include dependencies

namespace sys
{
 struct Mod
 {
  typedef void (*Global)();
  
  struct Entry
  {
   unsigned         index; //in init section
   const char*const name;
  };
//------------------------------------------ class methods
  static void start();
  static void stop();
 };
} 
#endif //EARLY_INIT
namespace sys
{
 //see linker script
 //see ld --build-id
 struct BuildID
 {
  const char*          name;
  const unsigned       type;
  const unsigned       descN;
  const unsigned char* desc;
  bool operator==(const BuildID& other) const; //TODO
 };

 const BuildID& buildId();
}
#endif //assembler
