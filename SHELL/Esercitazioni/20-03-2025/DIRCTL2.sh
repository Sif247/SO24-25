#!/bin/sh
#file comandi DIR.sh

case "$#" in 
0)
  echo "Nessun parametro -> contenuto directory corrente"
  ls -l | more
  exit 0
  ;;
1)
  echo "1 parametro -> procedo con i controlli"
  ;;
*)
  echo "Errore, hai passato $# parametri, devi passarne 1"
  exit 1
  ;;
esac

arg=$1


if [ -d $arg ]; then
   echo "E' una directory: " 
   ls -ld $arg
elif [ -f $arg ]; then 
     echo "E' un file: "
     ls -l $arg
else
     echo "Errore, non è ne un file ne una directory"
     exit 2
fi

