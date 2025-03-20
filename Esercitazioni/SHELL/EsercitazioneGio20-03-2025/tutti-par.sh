#!/bin/sh
#file comandi tutti-par.sh 

case $# in	#controlliamo il numero di parametri
0) echo "Errore: voglio dei parametri, mentre ne hai passati $#!" 
   exit 1;;
*) echo DEBUG-$# numero giusto di parametri!;;
esac
 
#se arriviamo qui siamo sicuri che siano stati passati dei parametri
#eseguiamo quanto richiesto e cioe' la stampa di tutti i parametri sia in forma aggregata ca che un parametro per volta
echo si sta eseguendo per tutti i parametri che sono: $*	#stampa aggregata
for i 
do
	echo Parametro = $i					#stampa di un parametro per volta
done

