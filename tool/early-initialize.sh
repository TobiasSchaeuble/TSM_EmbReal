#!/bin/bash
#-----------------------
#(c) H.Buchmann FHNW 2014
# ${1} early-initialize.xml
# ${2} home
#-----------------------
BIN=$(dirname ${0})
echo "extern const sys::Mod::Entry __InitSequence[]={"
java -jar ${BIN}/early-initialize.jar init
echo "	{0,0}" 
echo "};"
