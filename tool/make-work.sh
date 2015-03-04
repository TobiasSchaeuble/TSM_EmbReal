#------------------
#make-work.sh
#(c) H.Buchmann FHNW 2013
#we are on top
#------------------
SIGNATURE=.fbea039d-9be0-40a3-97df-d613a339aa98


function home
{
 while [ true ] 
 do 
  [[ $(pwd) = ${HOME} ]] && return 
  [[ -e ${SIGNATURE} ]] && { SUPERFLUOUS=$(pwd); return; }
  cd ..
 done
}

home

SUPERFLUOUS=$(pwd)
BOARD=arduino-due/board/

cd ${BOARD}
echo "$Creating infrastructure for '${BOARD}'"
[[ ! -d work ]] && mkdir work
cd work
java -jar ${SUPERFLUOUS}/tool/projects.jar makefile ../config/projects.xml ${SUPERFLUOUS} \
>Makefile
make namespace
