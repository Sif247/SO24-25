#!/bin/sh
#ATTENZIONE: Poco significativo se non si passano parametri (meglio 4)
#con dei singoli comandi echo visualizziamo su standard output i singoli parametri, supponendo che ce ne siano almeno 4! Notare l'uso delle singole vigolette per inibire ogni sostituazione!
echo I PARAMETRI SONO
echo 'Il valore di $1 ===>' $1
echo 'Il valore di $2 ===>' $2
echo 'Il valore di $3 ===>' $3
echo 'Il valore di $4 ===>' $4
#ora, sempre con il comando echo, visualizziamo su standard output i parametri in modo aggregato
echo 'Il valore di $* (TUTTI I PARAMETRI, a parte $0) ===>' $*
#sempre con il comando echo, visualizziamo su standard output i NUMERO dei parametri
echo 'Il valore di $# (NUMERO DEI PARAMETRI, sempre a parte $0) ===>' $#
#usiamo adesso il comando shift
shift
#rieseguiamo i comandi precedenti, dopo aver avvisato che abbiamo usato il comando shift; N.B. nelle singole visualizzazione, sulla base della precedente supposizione, visualizziamo solo 3 parametri
echo DOPO LO SHIFT, SONO
echo 'Il valore di $1 ===>' $1
echo 'Il valore di $2 ===>' $2
echo 'Il valore di $3 ===>' $3
echo 'Il valore di $* (TUTTI I PARAMETRI, a parte $0) ===>' $*
echo 'Il valore di $# (NUMERO DEI PARAMETRI, sempre a parte $0) ===>' $#
#proseguiamo verificando il valore di ritorno del comando ls, usato su due nomi diversi di file
ls DIR.sh
echo 'Il valore di $? (VALORE DI RITORNO ULTIMO COMANDO) ===>' $?
ls pippo 
echo 'Il valore di $? (VALORE DI RITORNO ULTIMO COMANDO) ===>' $?
#terminiamo visualizzando su standard output il PID del processo che sta eseguendo questo script
echo 'Il valore di $$ (NUMERO DEL PROCESSO IN ESECUZIONE) ===>' $$
