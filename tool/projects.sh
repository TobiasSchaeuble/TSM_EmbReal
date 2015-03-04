#!/bin/bash
#-----------------------
#(c) H.Buchmann FHNW 2011
# ${1} action
# ${2} project
#-----------------------
BIN=$(dirname ${0})
. ${BIN}/setup.sh
#http://stackoverflow.com/questions/1221833/bash-pipe-output-and-capture-exit-status
res=0
case ${1} in  
 publicId|dtd)
 java -jar ${BIN}/projects.jar ${@} 
 res=${?}
 ;;
 makefile|graph|prj|files)
 java -jar ${BIN}/projects.jar ${1} ${2} ${HOME_BASE} ${3} 2>&2| sed "s/'home'//"
 res=${PIPESTATUS}
 ;;
 *) java -jar ${BIN}/projects.jar makefile ../config/projects.xml ${HOME_BASE}
 res=${?}
 ;;
esac

[[ ${res} -gt 0 ]] && \
{ cat << EOF
#minimal makefile for making projects
#$(date)
projects:
	${BIN}/projects.sh makefile ../config/projects.xml  > Makefile
EOF
}

exit 0
