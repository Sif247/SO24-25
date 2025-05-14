#!/bin/sh
#file comandi trova-file.sh 

case $# in 							#controlliamo che sia invocato con un solo parametro: usato un case perche' e' piu' versatile!
1) echo DEBUG-OK un solo parametro $1 ;;			#caso giusto!
*) echo Errore: voglio un parametro, mentre ne hai passati $#! Uso: $0 file	#casi NON giusti! In generale e' utile, in caso di errore, indicare il modo corretto di invocazione!
   exit 1;;
esac

#se arriviamo qui siamo sicuri che sia stato passato esattamente un parametro
#controlliamo che il primo parametro sia dato in forma relativa semplice; come fatto in altre occasioni in realta' controlliamo la condizione negata e cioe' e' un errore se $1 contiene un carattere / all'inizio o in una qualunque altra posizione! 
case $1 in
*/*) echo Errore: $1 non in forma relativa semplice 		#notare che questa forma di controllo ingloba anche il caso /*
     exit 2;;
*) ;;
esac

#se arriviamo qui siamo sicuri che sia stato passato un parametro in forma relativa semplice
if test -f $1 	#controlliamo che sia un file
then
	echo -n "DEBUG-il file $1 esiste e si trova in "	#stampa aggiunta, ma non richiesta; N.B. Uso di -n e doppie virgolette
	pwd
	echo Trovato file $1 nella dir corrente e il suo nome assoluto e\' `pwd`/$1			#UNICA STAMPA RICHIESTA
else 	echo -n "DEBUG-non esiste un file di nome $1 in " 	#stampa aggiunta, ma non richiesta; IDEM come sopra!
	pwd
fi
