#!/bin/sh
#file comandi for4Ter.sh

#supponiamo che in un file (il cui nome relativo semplice verra' passato come parametro) siano stati memorizzati i nomi di alcuni file insieme con la loro lunghezza in linee

#controllo sul numero di parametri
case $# in
	1) echo DEBUG-numero di parametri esatto $#;;
	*) echo Errore: voglio un parametro, mentre ne hai passati $#
	   exit 1;;
esac

#se arriviamo qui siamo sicuri che sia stato passato esattamente un parametro
#controlliamo che $1 sia un nome relativo semplice
case $1 in
*/*) echo ERRORE non nome relativo semplice
     exit 2;;
*)   echo DEBUG-il nome del file passato = $1, quindi nome relativo semplice;;
esac

#se arriviamo qui siamo sicuri che sia stato passato un parametro in forma relativa semplice
#controlliamo che $1 esista come file e sia leggibile! N.B. Come gia' spiegato facciamo il controllo negato e quindi per la regola/legge di DE MORGAN controlliamo che se non e' un file o non e' leggibile diamo un errore e usciamo!
if test ! -f $1 -o ! -r $1
then    echo Errore: $1 non file oppure non leggibile
        exit 2
fi

#se arriviamo qui il file $1 e' un file esistente E leggibile!
c=0	#variabile che ci serve all'interno del for per capire se siamo su un elemento dispari (nome file) o su un elemento pari (numero di linee)

#N.B. Il codice che segue e' stato semplificato rispetto al codice di for4Bis.sh visto a lezione, dato che nei casi reali il contenuto del file $1 verra' 'GENERATO' da uno script e quindi possiamo essere sicuri che gli elementi di posto dispari siano nomi di file leggibili! Quindi abbiamo eliminato tutti i controlli relativi e il codice che usava la variabile giusto!
for i in `cat $1`	 #la lista usata nel for corrisponde al contenuto di un file! Se il file fosse vuoto, il for non eseguira' nulla!
do
 	c=`expr $c + 1` 		#ad ogni iterazione incrementiamo il contatore
        if test `expr $c % 2` -eq 1    	#se il contatore e' dispari
	then 
		echo Elemento dispari, quindi nome di file $i
	       	echo DEBUG-VISUALIZZAZIONE DI $i
		echo ===        #inseriamo delle separazioni per rendere piu' chiara la stampa
		cat $i		#mostriamo il contenuto
	       	echo ===        #inseriamo delle separazioni per rendere piu' chiara la stampa
        else 				#se il contatore e' pari
		echo Elemento pari, quindi lunghezza in linee del file appena visualizzato = $i 
        fi
done
