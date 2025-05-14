#!/bin/sh
#file comandi for2.sh

for i in p*	#la lista del for sara' costituita da tutti i nomi di file/directory il cui nome inizia per p; se tale lista fosse nulla il for non eseguira' nulla!
do
	echo ELEMENTO CORRENTE: $i	#stampiamo il nome corrente
	if test -f $i			#verifichiamo che sia un file. N.B. In questo caso il fatto che NON sia un file NON e' un errore e quindi NON usiamo il controllo NEGATO!  
	then 
		if test -r $i		#dato che il testo indica di visualizzare il contenuto, effettuiamo un controllo che il file corrente sia leggibile. IDEM COME SOPRA!
		then
			echo DEBUG-VISUALIZZAZIONE DI $i
			echo ===	#inseriamo delle separazioni per chiarezza
			cat $i
			echo ===	#inseriamo delle separazioni per chiarezza
		else 	echo il file $i NON e\' leggibile 	#NOTARE CHE SE NELLE STRINGHE STAMPATE CON echo VOGLIAMO USARE L'APOSTROFO (in questo caso usato come accento) DOBBIAMO USARE IL CARATTERE DI ESCAPE!
		fi
	else 	echo "L'elemento $i NON e' un file"
		#si potrebbe dare per scontato che se non e' un file e' una directory
	fi
done
