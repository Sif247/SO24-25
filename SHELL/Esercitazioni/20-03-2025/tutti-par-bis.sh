#!/bin/sh

if [ $# -eq 0 ]; then
	echo "Errore, deve esserci almeno 1 o più parametri! "
	exit 1
else
	count=0
	echo "Parametri aggregati: $*"
	for i in "$@"; do
		echo "il parametro $count è: $i"
		count=$(($count + 1))
	done
fi
exit 0
