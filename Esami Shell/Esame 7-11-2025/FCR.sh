#!/bin/sh

DIR="$1"
TMP="$2"
shift 2

Count=0

for F in "$DIR"/*
do
    if test -d $F
    then
        ./FCR.sh $F $TMP $@
    fi
    if test -f "$F" -a -r "$F"
    then
        occorrenze=1
        for C in "$@"
        do
            if  ! grep -q "$C" "$F"
            then
                occorrenze=0
                break
            fi
        done
        if test $occorrenze -eq 1
        then
            echo "$F" >> "$TMP"
            Count=1
        fi
    fi
done

if test $Count -eq 1 
then
        echo "+ $DIR"
    else
        echo "- $DIR"
fi