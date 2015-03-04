#------------------
#reset.sh
#(c) H.Buchmann FHNW 2014
#------------------
DEVICE=/dev/ttyACM0
stty -F ${DEVICE} 1200
cat << EOF > ${DEVICE}


EOF
 
