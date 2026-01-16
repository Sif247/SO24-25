#!/bin/sh

DIR=$1
TMP=$2

shift 2

ok=0

for F in $DIR/*
do
    trovato=0
    if test -f $F -a -r $F
    then
        for C in $@
        do
            grep -q $C $F
            if test $? -eq 0
            then
                trovato=1
                break
            else
                trovato=0
            fi
        done

        if test $trovato -eq 1
        then
            echo $F >> $TMP
            ok=1
        fi
    fi

    if test -d $F -a -x $F
    then
        FCR.sh $F $TMP $@
    fi
done


if test $ok -eq 1
then
    echo "+ $DIR"
else
    echo "- $DIR"
fi