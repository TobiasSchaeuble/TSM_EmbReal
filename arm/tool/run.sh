#------------------------
#run.sh
#(c) H.Buchmann FHNW 2011
#$Id$
#accessible from work
#------------------------
if [ -z ${1} ]
  then echo "usage ${0} imageFile [DEBUG]"
       exit 1
fi

if [ ! -f ${1} ]
   then echo "File ${1} dont exists"
        exit 1
fi
DEB="-${2}"

if [ ${DEB} = "-DEBUG" ]
   then DEBUG='-s -S'
        echo "debug mode"
fi

IMG=${1}
IMGFILE=${IMG}.img
if [ -f ${IMGFILE} ] 
 then IMG=${IMGFILE}
fi
echo "Image = ${IMG}"

#debug port 1234
#DEBUG='-s -S'
MACHINE=realview-eb
#MACHINE=versatileab

#QEMU=../../../qemu/bin/
QEMU=
${QEMU}qemu-system-arm -M ${MACHINE} -kernel ${IMG} \
${DEBUG} \
-serial stdio -sdl -display sdl


#-chardev pipe,id=console,path=console
#-nographic
stty echo
