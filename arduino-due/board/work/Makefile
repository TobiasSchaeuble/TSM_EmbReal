#Makefile Tue Mar 03 17:50:07 CET 2015
# projectsFile: ../config/projects.xml
# projects name: Arduino-Due
# (c) H.Buchmann FHNW 2012

_dp_PROJECTS_XML=\
	../config/projects.xml
#---------------------- (search
_dp_HOME?=\
	/home/tobias/Documents/fhnw-ime-mse
_dp_SRC_DIRS=\
	${_dp_HOME}/arduino-due/board/namespace ${_dp_HOME}/arduino-due/soc/3X/namespace ${_dp_HOME}/arduino-due/soc/namespace ${_dp_HOME}/arduino-due/cortex-m/namespace ${_dp_HOME}/arduino-due/arm/namespace\
	${_dp_HOME}/arduino-due/namespace ${_dp_HOME}/src/generic/namespace
vpath %.cc ${_dp_SRC_DIRS}
vpath %.c ${_dp_SRC_DIRS}
vpath %.h ${_dp_SRC_DIRS}
vpath %.S ${_dp_SRC_DIRS}
#---------------------- search)
#---------------------- (namespace
_dp_NAMESPACE=\
	 io/ascii math sys sys/abi\
	sys/boot sys/deb sys/mem sys/reg test\
	util
#---------------------- namespace)
#---------------------- (pre
#uncomment EARLY_INIT 
# for deriving init sequence at link time 
EARLY_INIT=EARLY_INIT



#----------------- the tools  
TC=../tc/bin/arm-none-linux-gnueabi-
CC=${TC}gcc
CXX=${TC}g++

CLANG_OPTIONS=-std=c++11 -target armv7m--eabi -integrated-as
#CC=clang++ ${CLANG_OPTIONS}
#CXX=${CC}

AS=${TC}as
LD=${TC}ld
NM=${TC}nm

OBJCOPY=${TC}objcopy

LIBGCC_DIR:=$(dir $(shell ${CXX} --print-libgcc-file-name))
LIBGCC:=-L${LIBGCC_DIR} -lgcc
 
CPPFLAGS= \
 -include "sys/sys.h"\
 $(foreach d,$(_dp_SRC_DIRS),-I $(d)) \
 -DEARLY_INIT \
 -DSYS_SYS_SHOW_STARTUP\
 -DNO_LONG_DIV \
 -DNO_FLOATS
 
CPU=cortex-m3
CFLAGS=-O2 -std=c++11 -mcpu=${CPU} -mthumb \
             -fomit-frame-pointer\
	     -fpermissive \
             -fno-exceptions \
	     -fuse-cxa-atexit \
	     -nostdinc\
	     -fno-builtin\
	     -Wreturn-type\
	     -Wall\
	     -fno-rtti\
	     -fno-unwind-tables \


CXXFLAGS=${CFLAGS}
#----------------- rule patterns
%.o:	%.S; ${CC} ${CPPFLAGS} -E ${<} | ${AS} -mcpu=${CPU} -o ${@}

SHOW_NM=@${NM} ${^}
SHOW_INIT_SEQUENCE=${NM} ${^} | ${BIN_HOME}/early-initialize.sh

INIT_SEQUENCE=${NM} ${^} | \
	${BIN_HOME}/early-initialize.sh | \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -x c++ -o init-sequence.o -

LINK=${INIT_SEQUENCE} && \
	${LD} -o ${@} ${^} init-sequence.o ${LIBGCC} --Map $@.map --build-id --script ../config/layout.ld && \
	${OBJCOPY} -O binary ${@} ${@}.bin

#use GRAPH for creating a dependency graph
GRAPH=@${NM}  ${^} | \
 java -jar ${_dp_HOME}/tool/early-initialize.jar graph  | dot -Tpdf > ${@}.pdf
   
   ARCHITECTURE=cortex-m4
   ENDIAN=LITTLE
   OPTIMIZE=2
   THUMB=yes
   BIN_HOME=${_dp_HOME}/tool
   SPECIAL_CXX=\
   -mfloat-abi=soft\
   -DNO_LONG_DIV \
   -DNO_FLOATS \
   -D'ATTRIBUTE_TEXT_STARTUP=__attribute((section(".text")))' \


  

#---------------------- pre)
#---------------------- (project list
_dp_PRJ_LIST=\
	memory-mapped-pointer-1 memory-mapped-pointer-3 memory-mapped-pointer-2 interrupt-demo memory-mapped-pointer-4\
	cpu-demo simple-uart interrupt-demo-1 interrupt-demo-2 interrupt-demo-3\
	led-demo interrupt-demo-4 startup-1 memory-mapped-extern-1 interrupt-demo-5\
	interrupt-demo-6
#---------------------- project list)
#---------------------- (project
memory-mapped-pointer-1:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o memory-mapped-pointer-1.o
	${LINK}
memory-mapped-pointer-3:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o memory-mapped-pointer-3.o
	${LINK}
memory-mapped-pointer-2:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o memory-mapped-pointer-2.o
	${LINK}
interrupt-demo:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o interrupt-demo.o
	${LINK}
memory-mapped-pointer-4:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o memory-mapped-pointer-4.o
	${LINK}
cpu-demo:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o cpu-demo.o\
	cpu-demo-ops.o
	${LINK}
simple-uart:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o simple-uart.o
	${LINK}
interrupt-demo-1:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o interrupt-demo-1.o\
	sys/reg/tc.o
	${LINK}
interrupt-demo-2:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o interrupt-demo-2.o\
	sys/reg/tc.o
	${LINK}
interrupt-demo-3:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o interrupt-demo-3.o\
	sys/reg/tc.o
	${LINK}
led-demo:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o led-demo.o\
	sys/led.o
	${LINK}
interrupt-demo-4:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o interrupt-demo-4.o\
	sys/reg/tc.o
	${LINK}
startup-1:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o test/startup-1.o
	${LINK}
memory-mapped-extern-1:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o memory-mapped-extern-1.o
	${LINK}
interrupt-demo-5:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o interrupt-demo-5.o\
	sys/reg/tc.o sys/reg/nvic.o
	${LINK}
interrupt-demo-6:\
	sys/mem/ram0.o sys/deb/deb.o sys/deb/deblow.o sys/reg/pio.o sys/reg/pio0.o\
	sys/hwreg.o sys/reg/uart.o sys/reg/uart0.o sys/boot/big-bang.o sys/abi/abi.o\
	sys/msg-1.o sys/msg.o io/ascii/out.o io/ascii/write.o util/float-conv.o\
	math/double.o sys/board.o sys/cortex-m.o sys/reg/scs.o sys/vtable.o\
	sys/trap.o sys/soc.o sys/reg/pmc.o sys/reg/wdt.o sys/reg/eefc.o\
	sys/boot/big-bang-continued.o sys/table.o sys/deb/deblow0.o sys/sys.o interrupt-demo-6.o\
	sys/reg/tc.o sys/reg/nvic.o
	${LINK}
#---------------------- project)
#---------------------- (module list
_dp_MOD_LIST=\
	sys/msg-1.o sys/reg/wdt.o sys/reg/tc.o cpu-demo-ops.o sys/abi/abi.o\
	io/ascii/out.o sys/mem/ram0.o sys/board.o sys/cortex-m.o io/ascii/write.o\
	sys/table.o util/float-conv.o sys/trap.o test/svc-handler.o sys/hwreg.o\
	sys/reg/pmc.o test/startup-1.o sys/reg/uart.o sys/reg/pio.o sys/deb/deb.o\
	sys/msg.o interrupt-demo-1.o interrupt-demo-2.o interrupt-demo-3.o interrupt-demo-4.o\
	interrupt-demo-5.o interrupt-demo-6.o sys/boot/big-bang-continued.o sys/reg/nvic.o sys/deb/deblow.o\
	sys/reg/scs.o sys/led.o sys/reg/uart0.o sys/vtable.o sys/soc.o\
	sys/reg/eefc.o memory-mapped-extern-1.o memory-mapped-pointer-1.o sys/reg/pio0.o memory-mapped-pointer-3.o\
	memory-mapped-pointer-2.o sys/sys.o interrupt-demo.o sys/boot/big-bang.o memory-mapped-pointer-4.o\
	math/double.o sys/deb/deblow0.o cpu-demo.o simple-uart.o led-demo.o
#---------------------- module list)
#---------------------- (modules
sys/msg-1.o:\
	sys/msg-1.cc sys/msg.h io/ascii/out.h io/ascii/write.h util/float-conv.h\
	math/double.h sys/deb/deb.h sys/deb/deblow.h
sys/reg/wdt.o:\
	sys/reg/wdt.cc sys/reg/wdt.h
sys/reg/tc.o:\
	sys/reg/tc.cc sys/reg/tc.h sys/hwreg.h sys/deb/deb.h sys/deb/deblow.h
cpu-demo-ops.o:\
	cpu-demo-ops.S
sys/abi/abi.o:\
	sys/abi/abi.cc sys/abi/abi.h sys/deb/deb.h sys/deb/deblow.h
io/ascii/out.o:\
	io/ascii/out.cc io/ascii/out.h
sys/mem/ram0.o:\
	sys/mem/ram0.cc sys/mem/ram0.h sys/deb/deb.h sys/deb/deblow.h
sys/board.o:\
	sys/board.cc sys/board.h sys/cortex-m.h sys/reg/scs.h sys/hwreg.h\
	sys/vtable.h sys/trap.h sys/soc.h sys/reg/pio.h sys/reg/pio0.h\
	sys/deb/deb.h sys/deb/deblow.h sys/reg/uart.h sys/reg/uart0.h sys/reg/wdt.h\
	sys/reg/pmc.h sys/reg/eefc.h sys/boot/big-bang-continued.h
sys/cortex-m.o:\
	sys/cortex-m.cc sys/cortex-m.h sys/reg/scs.h sys/hwreg.h sys/vtable.h\
	sys/trap.h sys/deb/deb.h sys/deb/deblow.h
io/ascii/write.o:\
	io/ascii/write.cc io/ascii/write.h io/ascii/out.h util/float-conv.h math/double.h\
	sys/deb/deb.h sys/deb/deblow.h
sys/table.o:\
	sys/table.cc sys/table.h
util/float-conv.o:\
	util/float-conv.cc util/float-conv.h math/double.h sys/deb/deb.h sys/deb/deblow.h
sys/trap.o:\
	sys/trap.cc sys/trap.h sys/deb/deb.h sys/deb/deblow.h
test/svc-handler.o:\
	test/svc-handler.S
sys/hwreg.o:\
	sys/hwreg.cc sys/hwreg.h
sys/reg/pmc.o:\
	sys/reg/pmc.cc sys/reg/pmc.h sys/hwreg.h
test/startup-1.o:\
	test/startup-1.cc sys/msg.h io/ascii/out.h io/ascii/write.h util/float-conv.h\
	math/double.h sys/deb/deb.h sys/deb/deblow.h
sys/reg/uart.o:\
	sys/reg/uart.cc sys/reg/uart.h sys/reg/uart0.h
sys/reg/pio.o:\
	sys/reg/pio.cc sys/reg/pio.h sys/reg/pio0.h sys/hwreg.h
sys/deb/deb.o:\
	sys/deb/deb.cc sys/deb/deb.h sys/deb/deblow.h
sys/msg.o:\
	sys/msg.cc sys/msg.h io/ascii/out.h io/ascii/write.h util/float-conv.h\
	math/double.h sys/deb/deb.h sys/deb/deblow.h
interrupt-demo-1.o:\
	interrupt-demo-1.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h sys/reg/tc.h sys/hwreg.h\
	sys/soc.h sys/cortex-m.h sys/reg/scs.h sys/vtable.h sys/trap.h\
	sys/reg/pio.h sys/reg/pio0.h
interrupt-demo-2.o:\
	interrupt-demo-2.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h sys/reg/tc.h sys/hwreg.h\
	sys/soc.h sys/cortex-m.h sys/reg/scs.h sys/vtable.h sys/trap.h\
	sys/reg/pio.h sys/reg/pio0.h
interrupt-demo-3.o:\
	interrupt-demo-3.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h sys/reg/tc.h sys/hwreg.h\
	sys/soc.h sys/cortex-m.h sys/reg/scs.h sys/vtable.h sys/trap.h\
	sys/reg/pio.h sys/reg/pio0.h
interrupt-demo-4.o:\
	interrupt-demo-4.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h sys/reg/tc.h sys/hwreg.h\
	sys/soc.h sys/cortex-m.h sys/reg/scs.h sys/vtable.h sys/trap.h\
	sys/reg/pio.h sys/reg/pio0.h
interrupt-demo-5.o:\
	interrupt-demo-5.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h sys/reg/tc.h sys/hwreg.h\
	sys/soc.h sys/cortex-m.h sys/reg/scs.h sys/vtable.h sys/trap.h\
	sys/reg/pio.h sys/reg/pio0.h sys/reg/nvic.h
interrupt-demo-6.o:\
	interrupt-demo-6.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h sys/reg/tc.h sys/hwreg.h\
	sys/soc.h sys/cortex-m.h sys/reg/scs.h sys/vtable.h sys/trap.h\
	sys/reg/pio.h sys/reg/pio0.h sys/reg/nvic.h
sys/boot/big-bang-continued.o:\
	sys/boot/big-bang-continued.cc sys/boot/big-bang-continued.h sys/abi/abi.h sys/deb/deb.h sys/deb/deblow.h
sys/reg/nvic.o:\
	sys/reg/nvic.cc sys/reg/nvic.h sys/hwreg.h
sys/deb/deblow.o:\
	sys/deb/deblow.cc sys/reg/pio.h sys/reg/pio0.h sys/hwreg.h sys/reg/uart.h\
	sys/reg/uart0.h
sys/reg/scs.o:\
	sys/reg/scs.cc sys/reg/scs.h sys/hwreg.h sys/vtable.h
sys/led.o:\
	sys/led.cc sys/led.h sys/reg/pio.h sys/reg/pio0.h sys/hwreg.h\
	sys/msg.h io/ascii/out.h io/ascii/write.h util/float-conv.h math/double.h\
	sys/deb/deb.h sys/deb/deblow.h sys/soc.h sys/cortex-m.h sys/reg/scs.h\
	sys/vtable.h sys/trap.h
sys/reg/uart0.o:\
	sys/reg/uart0.cc sys/reg/uart0.h
sys/vtable.o:\
	sys/vtable.cc sys/vtable.h
sys/soc.o:\
	sys/soc.cc sys/soc.h sys/cortex-m.h sys/reg/scs.h sys/hwreg.h\
	sys/vtable.h sys/trap.h sys/reg/pio.h sys/reg/pio0.h sys/reg/pmc.h
sys/reg/eefc.o:\
	sys/reg/eefc.cc
memory-mapped-extern-1.o:\
	memory-mapped-extern-1.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h sys/soc.h sys/cortex-m.h\
	sys/reg/scs.h sys/hwreg.h sys/vtable.h sys/trap.h sys/reg/pio.h\
	sys/reg/pio0.h
memory-mapped-pointer-1.o:\
	memory-mapped-pointer-1.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h
sys/reg/pio0.o:\
	sys/reg/pio0.cc sys/reg/pio0.h
memory-mapped-pointer-3.o:\
	memory-mapped-pointer-3.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h sys/soc.h sys/cortex-m.h\
	sys/reg/scs.h sys/hwreg.h sys/vtable.h sys/trap.h sys/reg/pio.h\
	sys/reg/pio0.h
memory-mapped-pointer-2.o:\
	memory-mapped-pointer-2.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h sys/soc.h sys/cortex-m.h\
	sys/reg/scs.h sys/hwreg.h sys/vtable.h sys/trap.h sys/reg/pio.h\
	sys/reg/pio0.h
sys/sys.o:\
	sys/sys.cc sys/sys.h sys/deb/deb.h sys/deb/deblow.h
interrupt-demo.o:\
	interrupt-demo.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h
sys/boot/big-bang.o:\
	sys/boot/big-bang.S
memory-mapped-pointer-4.o:\
	memory-mapped-pointer-4.cc sys/deb/deb.h sys/deb/deblow.h sys/msg.h io/ascii/out.h\
	io/ascii/write.h util/float-conv.h math/double.h sys/soc.h sys/cortex-m.h\
	sys/reg/scs.h sys/hwreg.h sys/vtable.h sys/trap.h sys/reg/pio.h\
	sys/reg/pio0.h
math/double.o:\
	math/double.cc math/double.h
sys/deb/deblow0.o:\
	sys/deb/deblow0.S
cpu-demo.o:\
	cpu-demo.cc sys/msg.h io/ascii/out.h io/ascii/write.h util/float-conv.h\
	math/double.h
simple-uart.o:\
	simple-uart.cc
led-demo.o:\
	led-demo.cc sys/msg.h io/ascii/out.h io/ascii/write.h util/float-conv.h\
	math/double.h sys/led.h sys/reg/pio.h sys/reg/pio0.h sys/hwreg.h\
	sys/deb/deb.h sys/deb/deblow.h
#---------------------- modules)
#---------------------- (post
projects:
	${BIN_HOME}/projects.sh makefile ${_dp_PROJECTS_XML} > Makefile
files:
	@java -jar ${BIN_HOME}/projects.jar files ${_dp_PROJECTS_XML} ${_dp_HOME} | sort
all:	${_dp_PRJ_LIST}
clean:	
	rm -f ${_dp_MOD_LIST} ${_dp_PRJ_LIST}
namespace:
	mkdir -p ${_dp_NAMESPACE}

#general rules
# all depends on sys/sys.h
   ${_dp_MOD_LIST}: sys/sys.h
  

#---------------------- post)
