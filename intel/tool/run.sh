#---------------------
#run.sh  
#(c) H.Buchmann FHNW 2012
#$Id$
#calling:
# run.sh [image] 
# default image ../sos.iso
#we are in work
#---------------------
IMAGE=../sos.iso
if [ ! -z ${1} ] 
 then IMAGE=${1}
fi 
if [ ! -e ${IMAGE} ]
 then echo "${IMAGE} dont exists"
      exit 1
fi
qemu-system-i386  -cdrom ${IMAGE}
