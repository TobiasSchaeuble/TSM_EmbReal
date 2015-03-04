#--------------------
#flash.sh
#(c) H.Buchmann FHNW 2014
# we are in work
#--------------------
FILE=${1%.bin}.bin
[[ ! -f ${FILE} ]] && { echo "usage ${0} image"; exit 1; }
DEV=/dev/ttyACM0
stty -F${DEV} 1200
ARDUINO=../tools/arduino
${ARDUINO} dtroff ${DEV}
${ARDUINO} dtron ${DEV}
sleep 1
../tools/bossac -e -w -v -b ${FILE}
stty -F${DEV} 115200
${ARDUINO} dtroff ${DEV}
${ARDUINO} dtron ${DEV}
