#----------------------
#Makefile 
#(c) H.Buchmann FHNW 2012
#$Id$
#see http://www.tldp.org/LDP/lkmpg/2.6/html/x181.html
#called by linux Makefile
#----------------------
#obj-m += simple-module.o
obj-m += simple-device.o 
#obj-m += simple-kbd.o
obj-m += simple-rtc.o
