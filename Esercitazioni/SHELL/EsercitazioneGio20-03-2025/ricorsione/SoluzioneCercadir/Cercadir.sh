#!/bin/sh
#file comandi Cercadir.sh: la ricerca della directory viene fatta in breadth-first

cd $1	#ci spostiamo nella directory in cui dobbiamo fare la ricerca per questa invocazione

#OSSERVAZIONE IMPORTANTE: SE AVESSIMO FATTO UN if COME NELLA VERSIONE CHE CERCAVA I FILE INSERENDO CHIARAMENTE test -d AVREMMO IL PROBLEMA CHE NON SI TERREBBE IN CONTO IL CASO IN CUI IL NOME RELATIVO SEMPLICE PASSATO POSSA ESSERE QUELLO DELLA DIR DI PARTENZA! QUINDI E' OPPORTUNO CHE FACCIAMO QUESTO CONTROLLO CON UN CASE!
case $1 in
*/$2) 	#in questo modo controlliamo anche il nome della gerarchia di partenza!
	echo la directory $2 si trova in `pwd` ;;	#trovata directory e quindi stampiamo il nome relativo semplice e in quale directory si trova
esac

#passiamo ora alla parte ricorsiva
for i in *
do
	if test -d $i -a -x $i 
	then
		#stampa di debugging
		echo DEBUG-Stiamo per esplorare la directory `pwd`/$i
		#invocazione ricorsiva: ATTENZIONE NOME ASSOLUTO dir!!!
		$0 `pwd`/$i $2	#possiamo usare $0
	fi
done
