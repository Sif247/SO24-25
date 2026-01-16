#!/bin/sh

if test $# -lt 2
then
    echo "Errore: numero parametri insufficienti, almeno 2"
    exit 1
fi

if test ! -d $1 -o  ! -x $1
then
    echo "$1 non è una directory o non è attraversabile"
    exit 2
fi

DIR=$1
shift

for C in $@
do
    case $C in 
    ?) ;;
    *) echo "Errore: $C non è un singolo carattere"
       exit 3;;
    esac
done

PATH=`pwd`:$PATH
export PATH

TMP=/tmp/file_$$
> $TMP

FCR.sh $DIR $TMP $@

N=`wc -l < $TMP`
echo "Total files: $N"

rm $TMP
