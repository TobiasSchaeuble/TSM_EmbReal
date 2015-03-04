/*--------------------
  sys-call
  (c) H.Buchmann FHNW 2013
  [1] x86_64-abi-0.95.pdf
 --------------------- */
.global main
.text
/* see [1] A.2.1 Linux Kernel Conventions 
 %eax call number
 the registers %rdi, %rsi, %rdx, %rcx, %r8 and %r9
 
*/

main:
 /* sys_write        %eax 1 for write see unistd_64.h 
       int      fd   %rdi the file id 0 for stdout
      char*      s   %rsi the string
  unsigned  length   %rdx  of string 
 */ 
 mov $1  ,%eax /* the call number */
 mov $0,  %rdi /* the stdout */
 mov $msg,%rsi /* address */ 
 mov $6,  %rdx /* size of string */
 syscall

 jmp main  /* do it again and again */
 
 msg: 
 	.ascii "Hello\n"
    
