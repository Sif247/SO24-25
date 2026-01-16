#!/bin/sh

if test $# -lt 3
then
    echo "Errore: numero di parametri insufficiente. "
    exit 1
fi

case $1 in
*[!0-9]*)
    echo "Errore $1 non è un numero intero"; exit 2;;
*) 
    if test $1 -le 0 -o $1 -ge 20
    then
        echo "Errore $1 è maggiore o uguale a 20"
        exit 3
    fi ;;
esac

X=$1
shift

TMP=/tmp/nomiAssoluti
> $TMP

N=0


PATH=`pwd`:$PATH
export PATH

for G in $@
do
    if test ! -d $G -o ! -x $G 
    then
        echo "Errore: $G non è una directory o non è attravesabile"
        exit 4
    fi

    
    FCR.sh $X $TMP $G

done

N=`wc -l < $TMP`
echo "Numero di file trovati: $N"

rm $TMP