#!/bin/sh
#file comandi DIRCTL2.sh

echo DEBUG-SONO DIRCTL2.sh	#debugging
case $# in			#controlliamo con un case i vari casi
0) echo non sono stati passati parametri	#informiamo l'utente
   echo DEBUG-eseguo 'ls -l' paginato nella directory corrente
   ls -l | more			#eseguiamo ls -l in forma paginata usando il piping dei comandi
   exit 0;;			#in questo caso abbiamo terminato il compito assegnato e quindi per uscire con successo usiamo exit 0
1) echo passato un parametro $1;;		#informiamo l'utente
*) echo Errore: voglio o zero oppure un parametro, mentre ne hai passati $#
   exit 1;;					#informiamo l'utente dell'errore e usciamo appunto con un valore diverso da 0!
esac

#se arriviamo qui siamo sicuri che sia stato passato un singolo parametro
echo '$0 ===>' $0	#queste due stampe vanno sempre fatte
echo '$1 ===>' $1	#e quindi conviene non replicarle per i due singoli casi!
if test -f $1				#controlliamo se il primo parametro e' un file
then 	echo $1 e\' un file		#avvisiamo che siamo in presenza di un file
	echo "DEBUG-Ora eseguo ls -l $1" #altra visualizzazione di debugging!
	ls -l $1			 #esecuzione del comando ls -l
else
	if test -d $1	#controlliamo se e' una directory, anche se potrebbe non essere necessario, dato che se non e' un file e' al 99% una directory 
	then	echo $1  e\' una directory	  #avvisiamo che siamo in presenza di una directory
		echo "DEBUG-Ora eseguo ls -ld $1" #ancora debugging
		ls -ld $1			  #esecuzione in questo caso di ls -ld
	else	#altrimenti non esiste un elemento con nome $1
		echo $1 non file o non directory
	fi
fi
