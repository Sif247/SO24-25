#!/bin/sh
#file comandi con altro esempio di for in cui la lista specificata deriva dal comando cat su un file!

#supponiamo che nel file ttt siano stati memorizzati i nomi di alcuni file o directory
for i in `cat ttt` 	#la lista usata nel for corrisponde al contenuto di un file! Se il file fosse vuoto, il for non eseguira' nulla!
do
	echo ELEMENTO CORRENTE: $i	#come per for1.sh
	if test -f $i	#se e' un file. N.B. In questo caso il fatto che NON sia un file NON e' un errore e quindi NON usiamo il controllo NEGATO! 
	then 	
		if test -r $i           #dato che si vuole visualizzare il contenuto, effettuiamo un controllo che il file corrente sia leggibile. IDEM COME SOPRA!
		then
	        	echo DEBUG-VISUALIZZAZIONE DI $i
			echo ===        #inseriamo delle separazioni per chiarezza
			cat $i		#mostriamo il contenuto
		        echo ===        #inseriamo delle separazioni per chiarezza
		else    echo il file $i NON e\' leggibile #NOTARE CHE SE NELLE STRINGHE STAMPATE CON echo VOGLIAMO USARE L'APOSTROFO (in questo caso usato come accento) DOBBIAMO USARE IL CARATTERE DI ESCAPE!
		fi
	else	echo "L'elemento $i NON e' un file"
	fi
done
