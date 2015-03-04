#--------------------
#make-file-list.sh
#(c) H.Buchmann FHNW 2011
#$Id$
#parameters: root-dirs
#output to stdout
#--------------------
find ${*} -type f -iregex '^.+\.\([c|h|S]\)$'

