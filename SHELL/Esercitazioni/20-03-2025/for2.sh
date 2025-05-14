#!/bin/sh
#file comandi con primo esempio di for

for i in p*	#per tutti i file/directory della directory corrente (ATTENZIONE NON QUELLI IL CUI NOME INIZIA PER IL CARATTERE .)
do
	echo ELEMENTO CORRENTE $i	#visualizziamo il nome relativo semplice del file/directory
	if [ -f $i ] && [ -r $i ]; then
		echo "Il contenuto è: "
		echo "================"
		cat "$i"
		echo "================"
	elif [ -d $i  ]; then
		echo "L'elemento $i è una directory"
	else
		echo "Il file non è leggibile"
	fi
done
