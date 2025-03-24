#!/bin/sh
#file comandi Cercafile.sh: la ricerca dei file viene fatta in breadth-first

cd $1		#ci spostiamo nella directory in cui dobbiamo fare la ricerca per questa invocazione

if test -f $2	#verifichiamo se esiste un file con il nome fornito dall'utente
then
	echo il file $2 si trova in `pwd`	#trovato file e quindi stampiamo il nome relativo semplice e in quale directory si trova
fi

#passiamo ora alla parte ricorsiva
for i in *
do
	if test -d $i -a -x $i 
	then
		#stampa di debugging
		echo DEBUG-Stiamo per esplorare la directory `pwd`/$i
		#invocazione ricorsiva: ATTENZIONE NOME ASSOLUTO dir!!!
		Cercafile.sh `pwd`/$i $2
	fi
done
