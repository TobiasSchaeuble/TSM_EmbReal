#----------------------
#Makefile
#(c) H.Buchmann FHWN 2014
#----------------------
CC=clang++ -std=c++11 -integrated-as -arch cortex-m3
CXX=${CC}
VPATH=../namespace
TC=../tc/bin/arm-none-eabi-
CC=${TC}gcc
CXX=${TC}/g++
AS=${TC}as
LD=${TC}ld  --Map $@.map -N -n
OBJCOPY=${TC}objcopy

CPPFLAGS=$(patsubst %,-I%,$(subst :, ,${VPATH}))

CPU=cortex-m3
CFLAGS=-mtune ${CPU}
CXXFLAGS=${CFLAGS}

%.o:	%.S; ${CC} ${CPPFLAGS} -E ${<} | ${AS} -mcpu=${CPU} -o ${@}

%.bin:	%;${OBJCOPY} -O binary ${^} ${@}

%:	%.o; ${LD} -o ${@} ${^} --script ../config/layout.ld

first:		first.o
first.o:	first.S
