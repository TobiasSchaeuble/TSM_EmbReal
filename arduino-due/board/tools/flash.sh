#--------------------
#flash.sh
#(c) H.Buchmann FHNW 2014
# we are in work
#--------------------
FILE=${1%.bin}.bin
[[ ! -f ${FILE} ]] && { echo "usage ${0} image"; exit 1; }
DEV=/dev/ttyACM0
../tools/bossac -e -w -v -b ${FILE}
