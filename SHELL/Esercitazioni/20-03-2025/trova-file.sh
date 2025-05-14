#!/bin/sh

if [ $# -ne 1 ]; then
   echo "Errore, deve essere invocato esattamente 1 parametro"
   exit 1
fi

case "$1" in
/*) echo "è un percorso assoluto, devi inserine un nome semplice relativo"
    exit 2;;
*/*) echo "è un percorso relativo, devi inserine un nome semplice relativo"
    exit 3;;
esac

if [ -f $1 ]; then
   echo "il file si trova in: $(pwd)/$1"
else
   echo "il file non si trova nella directory corrente"
   exit 3
fi

 
