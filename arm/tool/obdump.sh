#--------------------
#objdump.sh
#(c) H.Buchmann FHNW 2012
#$Id$
#--------------------
../tc/bin/arm-none-linux-gnueabi-objdump --architecture=arm -D --target=binary  ${1}
