#!/bin/sh

DIR=$2
C=$1

for G in $DIR/*
do
    if test -d $G -a -x $G
    then
        dirname=$(basename $G)
        case $dirname in
        ?$C?$C) echo "condizione a/b verificate $G";;
        *) echo "Errore la directory $G non ha 4 caratteri o non sono uguali a $C nei caratteri pari"
        esac
    

        for F in $G/*
        do
            [ -e "$F" ] || continue

            if test -f $F -a -r $F -a -s $F
            then   
                TOT=`wc -l < "$F"` 
                if test `expr $TOT % 2` -eq 0
                then
                    echo "Condizione c verificata $F"
                fi
            fi
        done

        for sub in "$G"/*; do
            [ -d "$sub" ] && [ -x "$sub" ] && FCR.sh "$C" "$sub"
        done
    fi
done


