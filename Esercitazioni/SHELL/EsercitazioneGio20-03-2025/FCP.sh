#!/bin/sh
#file comandi FCP.sh

case $# in
1) echo DEBUG-Numero giusto parametri: $#;;
*) echo Errore: voglio un parametro, mentre ne hai passati $#
   exit 1;;
esac

#se arriviamo qui siamo sicuri che sia stato passato esattamente un parametro
case $1 in
/*) if test ! -d $1 -o ! -x $1	#se nome assoluto, allora controlliamo che sia una directory e che sia traversabile;  N.B. Come gia' spiegato facciamo il controllo negato e quindi per la regola/legge di DE MORGAN controlliamo che se non e' una directory o non e' traversabile diamo un errore e usciamo!
    then
	echo Errore: $1 directory non esistente o non traversabile
	exit 2
    fi;;
*) echo Errore: $1 non nome assoluto	#non e' nome assoluto
   exit 3;;
esac

#se arriviamo qui vuole dire che $1 e' il nome di una directory traversabile!
#invochiamo il secondo file comandi: se non si ha il percorso '.' nella variabile PATH chiaramente bisogna invocare con ./file-dir.sh $1
#dato che il file comandi file-dir.sh NON e' ricorsivo NON serve che settiamo la variabile PATH
file-dir.sh $1 
