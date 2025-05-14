#!/bin/sh
#file comandi ceutente.sh: invocazione ceutente.sh nomeutente &

case $# in	#controlliamo che sia stato passato un solo parametro
1) ;;
*) echo Errore: voglio un solo parametro, mentre ne hai passati $#
   exit 1;;
esac

#se arriviamo qui siamo sicuri che sia stato passato esattamente un parametro
until who | grep $1	#se la condizione e' falsa e cioe' non esiste ancora un utente con il nome indicato
do
	sleep 10        #sospendiamo il processo per 10 secondi
done
echo UTENTE $1 COLLEGATO	#appena la condizione sara' vera e quindi l'utente si sara' collegato, lo segnaliamo 
