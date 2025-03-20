#!/bin/sh
#file comandi DIRCTL1.sh

echo DEBUG-SONO DIRCTL1.sh		#visualizzazione di una informazione di puro debugging!
if test $# -ne 1 			#controlliamo il numero di parametri e se non e' uguale a 1 diamo un errore!
then 	echo Errore: voglio un parametro, mentre ne hai passati $#
	exit 1
fi

#se arriviamo qui siamo sicuri che sia stato passato esattamente un parametro
echo 'Il valore di $0 ===>' $0		#visualizziamo il valore di $0
echo 'Il valore di $1 ===>' $1		#visualizziamo il valore di $1	

if test -f $1				#controlliamo se il primo parametro e' un file
then 	echo $1 e\' un file		#avvisiamo che siamo in presenza di un file
	echo "DEBUG-Ora eseguo ls -l $1" #altra visualizzazione di debugging!
	ls -l $1			 #esecuzione del comando ls -l
else
	if test -d $1	#controlliamo se e' una directory, anche se potrebbe non essere necessario, dato che se non e' un file e' al 99% una directory 
	then	echo $1  e\' una directory	  #avvisiamo che siamo in presenza di una directory
		echo "DEBUG-Ora eseguo ls -ld $1" #ancora debugging
		ls -ld $1			  #esecuzione in questo caso di ls -ld
	else    #altrimenti non esiste un elemento con nome $1
	        echo $1 non e\' un file o non e\' una directory
	fi
fi
