#!/bin/sh
#file comandi un-solo-parametro.sh: invocazione un-solo-parametro.sh stringa

if test $# -ne 1	#controlliamo che sia stato passato esattamente un parametro 
then			#altrimenti diamo un errore
	echo Errore: voglio un parametro, mentre ne hai passati $#
  	exit 1
fi

#se arriviamo qui siamo sicuri che sia stato passato esattamente un parametro
#il controllo se nome assoluto, relativo o relativo semplice VA FATTO OBBLIGATORIAMENTE con un case!
case $1 in
  /*) echo "$1 e' un nome assoluto" ;;				#solo se inizia con il carattere / e' un nome assoluto
  */*) echo "$1 e' un nome relativo alla dir corrente" ;;	#se contiene il carattere / allora e' un nome relativo
  *) echo "$1 e' un nome relativo semplice" ;; 			#dato che non corrisponde ai casi precedenti e' sicuramente un nome relativo semplice!
esac
#NOTA BENE: abbiamo controllato solo che tipo di nome sia e non che sia il nome di un file o di una directory!
