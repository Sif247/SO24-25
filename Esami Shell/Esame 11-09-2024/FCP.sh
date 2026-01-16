#!/bin/sh

# Controllo numero parametri
if test $# -lt 3
then
    echo "Errore: numero parametri insufficienti"
    exit 1
fi

# Controllo X intero positivo
case $1 in
*[!0-9]*)
    echo "Errore: $1 non è un numero intero"
    exit 2;;
*)
    if test $1 -le 0
    then
        echo "Errore: X deve essere strettamente positivo"
        exit 3
    fi;;
esac

X=$1
shift

PATH=`pwd`:$PATH
export PATH

TMP=/tmp/nomi
> $TMP

# Q fasi
for G in $@
do
    if test ! -d "$G" -o ! -x "$G"
    then
        echo "Errore: $G non è una directory o non è attraversabile"
        exit 4
    fi

    FCR.sh "$X" "$TMP" "$G"
done

# Al termine di TUTTE le fasi
N=`wc -l < $TMP`
echo "Numero di directory trovate: $N"

rm $TMP
