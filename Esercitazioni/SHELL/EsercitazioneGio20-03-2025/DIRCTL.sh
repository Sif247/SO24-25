#!/bin/sh
#file comandi DIRCTL.sh

echo DEBUG-SONO DIRCTL.sh		#visualizzazione di una informazione di puro debugging!
if test $# -ne 1 			#controlliamo il numero di parametri e se non e' uguale a 1 diamo un errore!
then 	echo Errore: voglio un parametro, mentre ne hai passati $#
	exit 1
fi

#se arriviamo qui siamo sicuri che sia stato passato esattamente un parametro
echo 'Il valore di $0 ===>' $0		#visualizziamo il valore di $0
echo 'Il valore di $1 ===>' $1		#visualizziamo il valore di $1	
echo "DEBUG-Ora eseguo ls -l $1"	#altra visualizzazione di debugging!
ls -l $1				#esecuzione del comando ls -l
