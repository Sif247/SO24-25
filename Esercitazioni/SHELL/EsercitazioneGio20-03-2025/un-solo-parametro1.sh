#!/bin/sh
#file comandi un-solo-parametro1.sh: invocazione un-solo-parametro1.sh stringa

#si e' deciso, in questo caso, di fare il controllo sul numero parametri con un case

case $# in
1) echo DEBUG-OK un solo parametro = $1;;			#unico caso corretto
*) echo Errore: voglio un parametro, mentre ne hai passati $# 	#casi NON corretti!
   exit 1;;
esac

#se arriviamo qui siamo sicuri che sia stato passato esattamente un parametro
#il controllo se nome assoluto, relativo o relativo semplice VA FATTO OBBLIGATORIAMENTE con un case!
case $1 in
  /*) echo "$1 e' un nome assoluto" ;;				#solo se inizia con il carattere / e' un nome assoluto
  */*) echo "$1 e' un nome relativo alla dir corrente" ;;	#se contiene il carattere / allora e' un nome relativo
  *) echo "$1 e' un nome relativo semplice" ;; 			#dato che non corrisponde ai casi precedenti e' sicuramente un nome relativo semplice!
esac
#NOTA BENE: abbiamo controllato solo che tipo di nome sia e non che sia il nome di un file o di una directory!
