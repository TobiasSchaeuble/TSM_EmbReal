#-------------------------
#make-it.sh
#(c) H.Buchmann FHNW 2012
#$Id: make-it.sh 4939 2012-03-02 15:33:38Z hans.buchmann $
#see http://www.tldp.org/LDP/lkmpg/2.6/html/x181.html
#-------------------------
#we are in work
#before switching from host to target or vice versa
# make clean

#---------------------- for host system
export KERNEL=/lib/modules/$(uname -r)/build
make -C ${KERNEL} V=1 M=${PWD} ${@}

###---------------------- for target system
#. ../../4-kernel/config/common.sh #load common 
#export KERNEL=../../4-kernel/build
#make  -C ${KERNEL} \
#     ARCH=arm \
#     CROSS_COMPILE=../tc/bin/${PREFIX}- \
#     M=${PWD} $@
