#!/bin/sh

if [ $# -ne 1 ]; then
   echo "Errore: non è stato passato esattamente 1 parametro: "
   exit 0
else
   echo "parametro passato correttamente"
fi

case "$1" in
/*) echo "Percorso relativo" 
    exit 1;;

*/*) echo "Percorso assoluto"
     exit 2;;

*) echo "Nome semplice"
	exit 3;;
esac



