#!/bin/sh
#file comandi DIR.sh

echo DEBUG-SONO DIR.sh			#visualizzazione di una informazione di puro debugging!
echo 'Il valore di $0 ===>' $0		#visualizziamo il valore di $0
echo 'Il valore di $1 ===>' $1		#visualizziamo il valore di $1	
echo "DEBUG-Ora eseguo ls -l $1"	#altra visualizzazione di debugging!
ls -l $1				#esecuzione del comando ls -l
