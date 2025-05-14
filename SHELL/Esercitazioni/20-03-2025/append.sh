#!/bin/sh

if [ $# -eq 1 ]; then
	if [ ! -f $1 ]; then
        echo "ERRORE, Non è stato inserito un file  "
	exit 1
	fi

	echo "1 parametro inserito: scrivo in append:  "
	cat >> $1

elif [ $# -eq 2 ]; then
	if [ ! -f $1 ]; then
        echo "ERRORE, Non è stato inserito un file  "
	exit 2
        fi

        echo "2 parametri inseriti: scrivo in append il contenuto del primo nel secondo  "
        cat $1 >> $2
else
	echo "Errore, è stato un numero sbagliato di parametri."
	exit 3
fi




