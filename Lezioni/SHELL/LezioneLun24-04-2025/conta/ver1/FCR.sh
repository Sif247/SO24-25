#!/bin/sh
#file comandi ricorsivo che scrive il nome dei file trovati sul file il cui nome e' passato come secondo argomento

cd $1	#ci spostiamo nella directory in cui dobbiamo fare la ricerca per questa invocazione

for i in *	#per tutti i file/dir
do
	if test -f $i 	#se e' un file, dato che dobbiamo SOLO contare i file!
	then 	echo `pwd`/$i >> $2 #memorizziamo il nome assoluto nel file temporaneo (il cui nome e' stato passato come secondo parametro)	
	fi
done
#inseriamo una stampa di puro debug: UNA VOLTA VERIFICATO IL FUNZIONAMENTO POTREMO COMMENTARLA!
echo DEBUG-in `pwd` conta = `wc -l < $2` 

#passiamo ora alla parte ricorsiva
#OSSERVAZIONE: facciamo un for separato dato che la parte di ricorsione e' standard e quindirisulta piu' chiaro separarla da quanto fatto sopra!
for i in *
do
	if test -d $i -a -x $i
	then
		FCR.sh `pwd`/$i $2	#ATTENZIONE: il nome della dir va sempre passato in forma assoluta!
	fi
done
