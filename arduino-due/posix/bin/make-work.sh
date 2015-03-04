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
BOARD=eo3s/board/

cd ${BOARD}
for b in $(ls)
do
 echo "Creating infrastructure for '${b}'"
 mkdir -p ${b}/work
 pushd ${b}/work >/dev/null
 java -jar ${SUPERFLUOUS}/posix/bin/projects.jar makefile ../config/projects.xml ${SUPERFLUOUS} \
 >Makefile
 make namespace
 popd >/dev/null
done
