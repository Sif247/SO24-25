#!/bin/sh
if [ "$#" -ne 1 ]; then
	echo "Errore, deve essere invocato esattamente 1 parametro "
	exit 1
fi

case $1 in 
/*)
	if [ -d  "$1" ] && [ -x "$1" ]; then
		./file-dir.sh "$1" #invoco
	else
		echo "La directory non esiste oppure non è trasversabile"
		exit 3
	fi;;
*)
       echo "Deve essere un nome assoluto"
       exit 2;;
esac
   		
