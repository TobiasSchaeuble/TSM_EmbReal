#------------------------
#led.sh via sam-ba
# blinks led L
#(c) H.Buchmann FHNW 2014
#we are in work
#------------------------
#pin PB27 
POSIX=../../../../posix/bin
SAM_BA=${POSIX}/sam-ba

DEVICE=/dev/ttyACM0

PIOB=0x400E1000
LED=$((1<<27))
#${SAM_BA}
${SAM_BA} ${DEVICE} \
	w.w $((PIOB)) ${LED} \
	w.w $((PIOB+0x10)) ${LED}

while [ true ]
do
 ${SAM_BA} ${DEVICE} w.w $((PIOB+0x34)) ${LED} # clears led
 sleep 0.5
 ${SAM_BA} ${DEVICE} w.w $((PIOB+0x30)) ${LED} # set led
 sleep 0.5
done	
