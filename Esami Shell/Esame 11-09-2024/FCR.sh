#!/bin/sh

X=$1
TMP=$2
DIR=$3
LIV=$4

# Prima chiamata: livello = 1
if test -z "$LIV"
then
    LIV=1
fi

if test $LIV -eq $X
then
    trovato=0
    for F in $DIR/*
    do
        if test -f $F -a -r $F -a -s $F
        then
            trovato=1
            basename "$F" >> $TMP
        fi
    done

    if test $trovato -eq 1
    then
        # salvo nome assoluto directory
        echo "$G" >> "$TMP"
    fi

    exit 0
fi


for G in $DIR/*
do
    if test -d "$G" -a -x "$G"
    then
        FCR.sh "$X" "$TMP" "$G" `expr $LIV + 1`
    fi
done
