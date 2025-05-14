#!/bin/sh
#file comandi con primo esempio di for

for i in .*	#per tutti i file/directory della directory corrente (ATTENZIONE NON QUELLI IL CUI NOME INIZIA PER IL CARATTERE .)
do
	echo ELEMENTO CORRENTE $i	#visualizziamo il nome relativo semplice del file/directory
done
