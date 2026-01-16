#!/bin/sh

if test $# -lt 3
then 
    echo "Errore: numero di parametri insufficiente"
    exit 1
fi

if test ! -d "$1" -o ! -x "$1"
then 
    echo "non è una directory o non è attraversabile"
    exit 2;
fi

G=$1
shift

for C in $@
do 
    case $C in
        ?)  ;;
        *)  echo "Errore: parametro '$C' non è un singolo carattere" 
            exit 3;;
    esac
done

TMP=/tmp/file_$$
> $TMP

PATH=`pwd`:$PATH
export PATH

FCR.sh "$G" "$TMP" "$@"

TOT=`wc -l < "$TMP"`   
echo "Total files: $TOT"


rm "$TMP"   