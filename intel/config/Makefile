#------------------------------------------ 
#Makefile
#(c) H.Buchmann FHNW 2011
#$Id$
#TODO setup for 64 bit check with grub
#     make system without grub use sys/boot/iso-big-bang.S
#     look for a more elegant solution for making the rules
#     handle empty file make.rules
#------------------------------------------ 
#we are in work
# directories
#
# sos
#    src
#    intel
#       config
#       src
#       work

#------------------------------------------ <setup>
CC=gcc -m32                    #we are using 32 bit
CFLAGS=-std=gnu99              #for asm volatile
CFLAGS+=-fno-stack-protector   #easy stack handling
VPATH=../src:../../src         #where to look for the source files
                               # order
			       # 1: sos/intel/src
			       # 2: sos/src

#------------------------------------------ assembler pattern
%.o:	%.S;$(CC) ${CPPFLAGS} ${CFLAGS} -c -o ${@} ${<}

export CPPFLAGS=-I../src -I../../src 
#------------------------------------------ link pattern
# .settings 32 bit architecture
#     objcopy: creating binary image
# genisoimage: creating cd iso image appropriate for grub
%:	%.o;\
ld  -o${@} \
    --build-id=none \
    -m elf_i386 \
    --script=../config/grub.ld \
    -Map ${@}.map ${^} && \
objcopy --output-target=binary ${@} ../iso/${@} && \
genisoimage -R \
	   -graft-points \
           -bstage2_eltorito \
	   -no-emul-boot \
	   -boot-load-size 4 \
	   -boot-info-table \
       -o ../sos.iso ../iso	

#------------------------------------------ <source files>
#add here your source files typically c rsp. S files
SRC=hello-world.c stdio.c stdout.c io/ascii.c io/screen.c \
 sys/pic.c sys/pit.c sys/trap.c sys/trap0.S \
 io/kbd.c \
 sys/boot/grub-big-bang.S sys/start.c cpu-demo.c \
 cpu-demo-ops.S \
 vga-demo.c \
 clock-demo.c
 
SYSTEM=stdio.o stdout.o io/ascii.o io/screen.o sys/boot/grub-big-bang.o sys/start.o
#------------------------------------------ <applications>
hello-world:	hello-world.o ${SYSTEM}
cpu-demo:	cpu-demo.o cpu-demo-ops.o ${SYSTEM}
vga-demo:	vga-demo.o ${SYSTEM}
clock-demo:	clock-demo.o ${SYSTEM} io/kbd.o sys/trap.o sys/trap0.o sys/pic.o sys/pit.o

#------------------------------------------ rules
#at first time using make empty make.rules
include make.rules       # made by make rules

#------------------------------------------ <admin>
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
