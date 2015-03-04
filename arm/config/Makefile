#------------------------------------------ 
#Makefile
#(c) H.Buchmann FHNW 2010
#$Id$
#we are in work
#------------------------------------------ 
#figure out prefix automatically
PREFIX=$(patsubst %-gcc,%,${shell ls ../tc/bin/*gcc})
#PREFIX=../tc/bin/arm-fhnw-eabi
#PREFIX=../tc/bin/arm-none-eabi
$(info PREFIX=${PREFIX})
export PATH:=${shell pwd}/${PREFIX}/bin:${PATH}
#------------------------------------------ <setup>
CC=${PREFIX}-gcc
LD=${PREFIX}-ld
OBJCOPY=${PREFIX}-objcopy
CXX=${PREFIX}-g++
CFLAGS=-std=gnu9x -O2 -g 

CPPFLAGS+=-DIRQ_STACK_SIZE_WORD=0x20 \
          -DUNDEF_STACK_SIZE_WORD=0x20 \
	  -DABORT_STACK_SIZE_WORD=0x20 \
	  -DSTACK_SIZE_WORD=0x100 

LDFLAGS=-nostdlib -Wl,--script=../config/ram.ld -Wl,-Map -Wl,${@}.map
       # |              |----- the linker script
       # |-------------- no standard libs 

#------------------------------------------ link pattern
%:	%.o; rm -f ${@}.img
	$(CC) -o${@}  ${^} ${LDFLAGS} -lgcc
	${OBJCOPY} -O binary ${@} ${@}.img
#------------------------------------------ assembler pattern
%.o:	%.S;$(CC) ${CPPFLAGS} ${CFLAGS} -c -o ${@} ${<}


SOURCE_PATH=../src ../src/execution-environment  ../../src

VPATH=$(foreach s,${SOURCE_PATH},:${s})
export CPPFLAGS+=$(foreach s,${SOURCE_PATH},-I${s})

#------------------------------------------ <source files>
SRC=hello-world.c \
stdio.c io/ascii.c stdout.c \
sys/boot/big-bang.S sys/start.c \
accessing-hardware.c \
sys/timer.c timer-test.c \
sys/deb.c sys/deb0.S \
sys/sys.c \
sys/stack.c \
undef-trap-demo.c \
gic-test.c sys/gic.c sys/gic0.S \
io/lcd.c lcd-demo.c \
io/font.c \
io/screen.c \
io/uart-poll.c io/uart-irq.c \
ascii-test.c \
cpu-demo-ops.S cpu-demo.c \
sys/arm.c \
timer-trap-demo-hw.c \
timer-trap-demo-polling.c \
timer-trap-demo-irq.c \
common-access.c \
mmu-test.c sys/mmu.c \
swi-trap-demo.c \
uart-test.c \
page-fault-demo.c \
sys/coroutine.c sys/coroutine0.S coroutine-test.c coroutine-demo.c \
ps2-mouse-test.c \
io/mouse.c mouse-demo.c \
sys/thread.c thread-demo.c \
atomic.c \
clock.c \
sync-polling.c \
coroutines.c \
sync-threads.c \
interrupts.c \
async-polling.c \
async-threads.c \
uart-demo.c \
sergio-paganoni.c \

GIC=sys/gic.o sys/gic0.o

SYSTEM=sys/stack.o sys/arm.o sys/mmu.o io/uart-poll.o io/uart-base.o ${GIC} \
sys/deb.o sys/deb0.o stdio.o io/ascii.o stdout.o sys/boot/big-bang.o sys/start.o

all:	hello-world accessing-hardware timer-test cpu-demo \
 	undef-trap-demo swi-trap-demo page-fault-demo \
	timer-trap-demo-hw timer-trap-demo-polling timer-trap-demo-irq \
	common-access\
	gic-test\
	lcd-demo lcd-demo-0 ascii-test\
	mmu-test\
	coroutine-demo\
	thread-demo\
	sync-polling \
	coroutines\
	sync-threads\
	interrupts\
	async-polling\
	async-threads

#------------------------------------------ <applications>
hello-world:	hello-world.o ${SYSTEM}
accessing-hardware:	accessing-hardware.o ${SYSTEM}
timer-test:	timer-test.o sys/timer.o ${SYSTEM}

cpu-demo:	cpu-demo.o cpu-demo-ops.o ${SYSTEM}
sergio-paganoni:	sergio-paganoni.o ${SYSTEM}
#-----------------------------------------undef-trap-demo
undef-trap-demo:	undef-trap-demo.o ${SYSTEM}

#-----------------------------------------swi-trap-demo
swi-trap-demo:	swi-trap-demo.o ${SYSTEM}

#-----------------------------------------page-fault-demo
page-fault-demo:	page-fault-demo.o ${SYSTEM}

#-----------------------------------------timer-trap-demo
timer-trap-demo-hw:		timer-trap-demo-hw.o sys/timer.o ${SYSTEM}
timer-trap-demo-polling:	timer-trap-demo-polling.o sys/timer.o ${SYSTEM}
timer-trap-demo-irq:		timer-trap-demo-irq.o sys/timer.o sys/gic.o ${SYSTEM}


#-----------------------------------------common-access
common-access: 	common-access.o sys/timer.o ${SYSTEM}

#-----------------------------------------gic generic interrupt controller
gic-test:	gic-test.o sys/sys.o sys/gic.o sys/deb.o ${SYSTEM}

#-----------------------------------------lcd
LCD=io/lcd.o io/font.o
lcd-demo:	lcd-demo.o ${LCD} ${SYSTEM}
lcd-demo-0:	lcd-demo-0.o sys/deb.o ${SYSTEM}
ascii-test:	ascii-test.o io/screen.o io/lcd.o io/font.o ${SYSTEM}
clock:		clock.o io/lcd.o io/font.o ${SYSTEM}

#------------------------------- mmu-devel
mmu-test:	mmu-test.o sys/boot/big-bang.o sys/stack.o sys/mmu.o sys/deb.o


#------------------------------- concurrency 
coroutine-demo: coroutine-demo.o sys/coroutine0.o sys/coroutine.o ${SYSTEM}
coroutine-test: coroutine-test.o sys/coroutine0.o sys/coroutine.o ${SYSTEM}
thread-demo:	thread-demo.o sys/thread.o sys/coroutine0.o sys/coroutine.o ${SYSTEM}
atomic: 	atomic.o ${SYSTEM}

sync-polling:	sync-polling.o clock.o ${LCD} ${SYSTEM}
COROUTINE=sys/coroutine.o sys/coroutine0.o
coroutines:	coroutines.o clock.o ${COROUTINE} ${LCD} ${SYSTEM}
THREAD=${COROUTINE} sys/thread.o
sync-threads:	sync-threads.o clock.o ${THREAD} ${LCD} ${SYSTEM}  
interrupts:	interrupts.o clock.o io/uart-irq.o ${THREAD}  ${LCD} ${SYSTEM}
async-polling:	async-polling.o io/uart-irq.o clock.o ${THREAD} ${LCD} ${SYSTEM}
async-threads:	async-threads.o clock.o io/uart-irq.o ${THREAD} ${LCD} ${SYSTEM}
uart-demo:	uart-demo.o io/uart-irq.o ${THREAD} ${LCD} ${SYSTEM}
#------------------------------- mouse
ps2-mouse-test: ps2-mouse-test.o  ${SYSTEM}
mouse-demo:	mouse-demo.o io/mouse.o ${SYSTEM}	

#------------------------------- the rules made with make rules

include make.rules

#-------------------------------------- <admin>
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}
.PHONY dirs:
dirs:	
	mkdir -p $(sort $(dir ${SRC}))

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
	
