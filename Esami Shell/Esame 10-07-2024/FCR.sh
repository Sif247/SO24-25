#!/bin/sh

X=$1
TMP=$2
DIR=$3

# 1️⃣ Controllo dei file della directory corrente
Verifica_file=0
for F in $DIR/*
do
    if test -f "$F" -a -r "$F"
    then
        L=`wc -l < "$F"`
        if test $L -ge $X -a $L -lt 255
        then
            Verifica_file=1
            echo "$F" >> "$TMP"
        fi
    fi
done

# Se almeno un file valido, stampa la directory corrente
if test $Verifica_file -eq 1
then
    echo "$DIR"
fi

# 2️⃣ Ricorsione sulle sottodirectory (COME VOLEVI TU)
for G in $DIR/*
do
    if test -d "$G" -a -x "$G"
    then
        FCR.sh "$X" "$TMP" "$G"
    fi
done
