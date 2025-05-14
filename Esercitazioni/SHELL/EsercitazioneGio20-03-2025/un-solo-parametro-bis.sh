#!/bin/sh
#file comandi un-solo-parametro-bis.sh: invocazione un-solo-parametro-bis.sh stringa

#facciamo il controllo, diversamente da come fatto nel file un-solo-parametro1.sh, di nuovo con un if
if test $# -ne 1        #controlliamo che sia stato passato esattamente un parametro
then                    #altrimenti diamo un errore
	echo Errore: voglio un parametro, mentre ne hai passati $#
	exit 1
fi

#se arriviamo qui siamo sicuri che sia stato passato esattamente un parametro
#il controllo se nome assoluto, relativo o relativo semplice VA FATTO OBBLIGATORIAMENTE con un case!
case $1 in
  /*) echo "$1 e' un nome assoluto" 		#solo se inizia con il carattere / e' un nome assoluto
      if test -f $1				#verifichiamo se e' un file
      then echo "$1 e' il nome di un file"
      else 
	   if test -d $1 -a -x $1		#oppure verifichiamo se ' una directory traversabile	
	   then echo "$1 e' il nome di una directory traversabile" 
           else #altrimenti non esiste un elemento con nome $1
		echo $1 non file o non directory	
      	   fi 
      fi;;
  */*) echo "$1 e' un nome relativo alla dir corrente" ;;		#se contiene il carattere / allora e' un nome relativo
  *) echo "$1 e' un nome relativo semplice" ;; 	#dato che non corrisponde ai casi precedenti e' sicuramente un nome relativo semplice!
esac
