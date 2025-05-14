#!/bin/sh

if [ $# -ne 2 ]; then
	echo "Errore, devono essere inseriti esattamente 2 parametri."
	exit 1
fi
case "$1" in
*/*) echo "Errore, deve essere un nome relativo semplice."
    exit 2;;
esac

case "$2" in
*/*) echo "Errore, deve essere un nome relativo semplice."
    exit 3;;
esac

if [ ! -f $1 ] && [ ! -r $1 ]; then
        echo "Errore, i file " $1 " non è leggibile o non è leggibile "
        exit 4
fi

if [ -f $2 ]; then
	if [ ! -w $2 ]; then
        	echo "Errore, file " $2 " non scrivibile "
        	exit 5
	fi
else
	if [ ! -w . ]; then
                echo "Errore, file " $2 " non esiste e non ho il permesso di scrivere sulla directory "
                exit 5
	fi
fi

cat $1 >> $2
echo "Contenuto di $1 aggiunto ad $2"


