#!/bin/sh
#file comandi append.sh: invocazione append [dadove] sucosa

case $# in
1) cat >> $1;;		#se un solo parametro, si deve scrivere in append su tale file
2) cat < $1 >> $2;;	#se due parametri, si deve appendere il contenuto di $1 in $2
*) echo "Errore: voglio uno o due parametri, mentre ne hai passati $#! Uso: append.sh [dadove] sucosa"
   exit 1;; #notare che questo exit poteva essere omesso dato che poi lo script termina, ma e' meglio inserirlo per ritornare un valore diverso da 0!
esac
