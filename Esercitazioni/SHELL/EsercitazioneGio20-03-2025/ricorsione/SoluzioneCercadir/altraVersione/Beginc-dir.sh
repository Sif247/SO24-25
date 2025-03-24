#!/bin/sh
#file comandi Beginc-dir.sh

d=	#la variabile d serve per memorizzare o il primo parametro oppure la directory corrente
dr=	#la variabile dr serve per memorizzare il parametro che rappresenta il nome relativo semplice della directory (primo o secondo parametro a seconda dei casi)

case $# in
0) echo "ERRORE POCHI PARAMETRI - Usage is: $0 [directory] file" 
   exit 1;;
1) d=`pwd`; dr=$1;;	#nel caso di un solo parametro d viene settato alla directory corrente
2) d=$1; dr=$2;;	#nel caso di due parametri, salviamoli nelle variabili
*) echo "ERRORE TROPPI PARAMETRI - Usage is: $0 [directory] file"
   exit 2;;
esac

#se arriviamo qui siamo sicuri di aver ricevuto 1 o 2 parametri e che le variabili d e f hanno entrambe un valore
#controlliamo che d sia dato in forma assoluta; N.B. nel caso di un parametro non sarebbe necessario, ma dato che abbiamo ricondotto entrambi i casi ad un codice unico, lo facciamo sempre
case $d in
/*) if test ! -d $d -o ! -x $d 	#se nome assoluto, allora controlliamo che sia una directory e che sia traversabile;  N.B. Come gia' spiegato facciamo il controllo negato e quindi per la regola/legge di DE MORGAN controlliamo che se non e' una directory o non e' traversabile diamo un errore e usciamo!
    then
	echo Errore: $d non directory o non attraversabile
	exit 3
    fi;;
*) echo Errore: $d non in forma assoluta
   exit 4;;
esac

#controllo che dr sia dato in forma relativa semplice 
case $dr in
*/*) echo Errore: $dr non in forma relativa semplice 
     exit 5;;
*) ;;
esac

#controlli finiti: settiamo la variabile di ambiente PATH
PATH=`pwd`:$PATH
export PATH	#per compatibilita'

echo DEBUG-Beginc-dir.sh: Stiamo per esplorare la directory $d
Cercadir.sh $d $dr	 #invocazione del secondo file comandi (che e' quello RICORSIVO e fa in questo caso tutto il 'lavoro'!)
echo HO FINITO TUTTO
