#!/bin/sh
#file comandi che deve essere invocato con il nome assoluto di una directory
#versione che usa un file temporaneo

case $# in	#controlliamo di avere esattamente un parametro 
1)	echo DEBUG-OK numero di parametri $#;;
*)      echo Errore: voglio un solo parametro, mentre ne hai passati $# - Usage is $0 dirass 
	exit 1;;
esac

#se arriviamo qui vuol dire che e' stato passato un solo parametro
#ora controlliamo che sia il nome assoluto di una gerarchia e, nel caso, una directory traversabile
case $1 in
/*) if test ! -d $1 -o ! -x $1	#se nome assoluto, controlliamo sia una dir traversabile
    then
    	echo Errore: $1 non directory o non traversabile
	exit 2
    fi;;
*)  echo Errore: $1 non nome assoluto; exit 3;;
esac

#se arriviamo qui vuol dire che sono finiti i controlli sui parametri ed e' andato tutto bene
#quindi possiamo passare a settare la variabile di ambiente PATH e poi ad esportarla
PATH=`pwd`:$PATH
export PATH

#creiamo un file /tmp/conta$$ il cui nome verra' passato come ulteriore argomento al file comandi ricorsivo
> /tmp/conta$$	#usiamo $$ per dare sempre un nome differente a questo file temporaneo
#N.B. Se il testo di un esame dice di dare un nome specifico al file temporaneo NON bisogna aggiugere $$

#invocazione del secondo file comandi
FCR.sh $1 /tmp/conta$$   

#Andiamo a contare le linee del file /tmp/conta$$ che rappresentano i file trovati
echo Il numero totale di file della gerarchia = `wc -l < /tmp/conta$$` 

#In questo caso possiamo recuperare anche i nomi (assoluti) dei file e fare delle azioni specifiche su ognuno di essi (in questo caso controlliamo se leggibile e visualizziamo il contenuto)
for i in `cat /tmp/conta$$`
do
	#N.B. gli elementi presenti nel file temporaneo sono sicuramente nomi di file e quindi non serve inserire un if con il controllo che sia un file
	echo IL NOME ASSOLUTO DEL FILE TROVATO: $i #visualizziamo il nome assoluto del file trovato
	if test -r $i #se il file e' leggibile (che sia il nome di un file e' gia' stato verificato in FCR.sh)
	then	echo il suo contenuto e\' il seguente
		echo ===	#separazione per chiarezza
		cat $i		#visualizziamo il contenuto del file trovato
		echo ===	#separazione per chiarezza
	else 	echo il file $i NON e\' leggibile
	fi	
done

rm /tmp/conta$$ #da ultimo rimuoviamo il file temporaneo
