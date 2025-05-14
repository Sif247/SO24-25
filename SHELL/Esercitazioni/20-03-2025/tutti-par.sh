#!/bin/sh

if [ $# -eq 0 ]; then
	echo "Errore, deve esserci almeno 1 o più parametri! "
	exit 1
else
	echo "Parametri aggregati: $*"
	for i in "$@"; do
		echo "$i"
	done
fi
exit 0
