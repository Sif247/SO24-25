#!/bin/sh
#file comandi Cercafile1.sh: ricerca dei file e' diversa da Cercafile.sh dato che viene fatta in depth-first 

cd $1	#ci spostiamo nella directory in cui dobbiamo fare la ricerca per questa invocazione

#spostiamo prima la parte della ricorsione
for i in *
do
	if test -d $i -a -x $i 
	then
		#stampa di debugging
		echo DEBUG-Stiamo per esplorare la directory `pwd`/$i
		#invocazione ricorsiva: ATTENZIONE NOME ASSOLUTO dir!!!
		Cercafile1.sh `pwd`/$i $2
	fi
done

if test -f $2	#verifichiamo se esiste un file con il nome fornito dall'utente
then
	echo il file $2 si trova in `pwd`	#trovato file e quindi stampiamo il nome relativo semplice e in quale directory si trova
fi
