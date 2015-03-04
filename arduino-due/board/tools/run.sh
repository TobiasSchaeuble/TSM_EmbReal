#------------------------
#run.sh via sam-ba
# blinks led L
#(c) H.Buchmann FHNW 2014
#we are in work
#dont works properly 
#------------------------
#pin PB27 
POSIX=../../../../posix/bin
SAM_BA=${POSIX}/sam-ba

DEVICE=/dev/ttyACM0
START=0x20000800
VTOR=0xE000ED08
${SAM_BA} ${DEVICE} w.f ${START} ${1}

#reser
#G20000800#G20000800#
