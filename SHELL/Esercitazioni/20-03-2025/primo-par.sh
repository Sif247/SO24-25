#!/bin/sh

if [ $# -eq 0 ]; then
	echo "Errore, inserisci almeno un parametro! "
	exit 1;
fi

echo "Il primo parametro è $1"
shift 
echo "Gli altri parametri sono $@" 

