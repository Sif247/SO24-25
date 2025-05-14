#!/bin/sh
if [ $# -eq 0 ]; then
	echo "Errore, inserire almeno un parametro! "
	exit 1
fi

num=0
LAST=
LIST=

for i 
do
	count=$(($count + 1))
	if [ $count -ne $# ]; then
		LIST="$LIST $i"
	else
		LAST=$i
	fi

done

echo "L'ultimo parametro è: $LAST"
echo "Gli altri parametri sono: $LIST"




