#!/bin/sh

if test $# -lt 3
then
    echo "Errore: numero di parametri insufficienti"
    exit 1
fi

case $1 in
?)  ;;
*)  echo "Errore: il primo parametro deve contenere un solo carattere"
    exit 2;;
esac

C=$1
shift

for G in $@
do
    if test ! -d $G -o ! -x $G 
    then 
        echo "Errore: non è una directory o non è attraversabile"
        exit 3
    fi 

    case $G in
    /*)  ;;
    *)  echo "Errore: non è una directory con nome assoluto" 
        exit 4;;      
    esac

    PATH=`pwd`:$PATH
    export PATH

    TMP=0
    ./FCR.sh "$C" "$G" "$TMP"

done