#----------------------
#usb-dump.sh
#(c) H.Buchmann FHNW 2014
#----------------------
sudo modprobe usbmon
sudo chown root:wireshark /dev/usbmon*
sudo chmod g+rw /dev/usbmon*
#sudo cat /sys/kernel/debug/usb/usbmon/${1}u

