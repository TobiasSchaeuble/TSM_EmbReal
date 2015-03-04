#-----------------------
#ddd.sh
#(c) H.Buchmann FHNW 2012
#$Id$
#-----------------------
#we are in work
GDB=../tc/bin/arm-none-linux-gnueabi-gdb
ddd --debugger "${GDB} --command=../tool/target.gdb" ${1}

