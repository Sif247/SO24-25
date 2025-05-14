#!/bin/sh

if [ $# -ne 1 ]; then
   echo "Errore: non è stato passato esattamente 1 parametro: "
   exit 0
else
   echo "parametro passato correttamente"
fi

case "$1" in
/*) echo "Percorso assoluto"
    if [ -f "$1" ]; then
       echo "E' un file "
    elif [ -d "$1" ] && [ -x "$1" ]; then
       echo "E' una directory trasversale"
    else
       echo "Non è ne un file o una directory"
    fi;;       
*/*) echo "Percorso relativo";;
*) echo "Nome relativo semplice";;
esac



