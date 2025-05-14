#!/bin/sh
#file comandi file-dir.sh

cd $1 	#ci spostiamo nella directory il cui nome e' passato come parametro

F=0 	#variabile per contare i file
D=0  	#variabile per contare le directory

for i in * 	#per tutti i file/directory della directory corrente
do
	if test -f $i	#se e' un file
  	then
    		echo [F] `pwd`/$i	#stampiamo il nome premettendo un [F]
    		F=`expr $F + 1`		#incrementiamo il numero di file
  	else
		if test -d $i		#se invece e' una directory
		then 
    			echo [D] `pwd`/$i	#stampiamo il nome premettendo un [D]
    			D=`expr $D + 1`		#incrementiamo il numero di directory
		fi	
  	fi
done

#finita l'analisi degli elementi della directory corrente, per sicurezza controlliamo di non essere in una directory vuota
if test $F -eq 0 -a $D -eq 0 	
then
    echo "ATTENZIONE: la directory $1 e' vuota" #per questa visualizzazione si poteva usare anche `pwd`
    exit 3
fi

#se arriviamo qui vuole dire che $F e/o $D sono diversi da zero e quindi stampiamo i due conteggi
echo Numero di file presenti in $1 = $F		#vedi commento precedente per l'indicazione della directory corrente
echo Numero di directory presenti in $1 = $D
