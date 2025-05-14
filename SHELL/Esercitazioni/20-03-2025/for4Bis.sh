#!/bin/sh
#file comandi che parte da for4.sh ma considera che la lista ottenuta dal comando cat su un file abbia un formato specifico!

#supponiamo che nel file t siano stati memorizzati i nomi di alcuni file insieme con la loro lunghezza in linee
c=0		#variabile che ci serve all'interno del for per capire se siamo su un elemento dispari (nome file) o su un elemento pari (numero di linee)
giusto=1	#variabile che ci serve all'interno del for per capire se dobbiamo o meno visualizzare l'elemento pari

for i in `cat t` 	#la lista usata nel for corrisponde al contenuto di un file! Se il file fosse vuoto, il for non eseguira' nulla!
do
 	c=`expr $c + 1` 		#ad ogni iterazione incrementiamo il contatore
        if test `expr $c % 2` -eq 1    	#se il contatore e' dispari
	then 
		if test -f $i		#controlliamo sia il nome di un file
		then 	
			echo Elemento dispari, quindi nome di file $i
			if test -r $i           #dato che si vuole visualizzare il contenuto, effettuiamo un controllo che il file corrente sia leggibile
			then
	        		echo DEBUG-VISUALIZZAZIONE DI $i
				echo ===        #inseriamo delle separazioni per chiarezza 
				cat $i		#mostriamo il contenuto
		        	echo ===        #inseriamo delle separazioni per chiarezza 
			else    echo il file $i NON e\' leggibile #NOTARE CHE SE NELLE STRINGHE STAMPATE CON echo VOGLIAMO USARE L'APOSTROFO (in questo caso usato come accento) DOBBIAMO USARE IL CARATTERE DI ESCAPE!
				giusto=0	#resettiamo la variabile in modo da non stampare l'elemento pari seguente
			fi
		else 	echo "L'elemento dispari $i NON e' un file"
			giusto=0	#resettiamo la varibile in modo da non stampare l'elemento pari seguente
		fi
        else 				#se il contatore e' pari
		if test $giusto -eq 1	#controlliamo se dobbiamo visualizzare l'informazione
		then 	echo Elemento pari, quindi lunghezza in linee del file appena visualizzato = $i 
		else	giusto=1	#rimettiamo giusto a 1 per il prossimo elemento
		fi
        fi
done
