#!/bin/sh
if [ "$#" -ne 1 ]; then
	echo "Errore, serve esattamente un parametro"
	exit 1
fi

cd $1 || {
	echo "Errore, impossibile entrare nela directory $1"
	exit 2
}

num_file=0
num_dir=0

for i in *
do
	if [ -f $i ]; then
		echo "[F] $pwd/$i"
		num_file=$(($num_file + 1))
	else
		if [ -d $i ]; then
               		echo "[D] $pwd/$i"
                	num_dir=$(($num_dir + 1))
		fi
	fi
done

echo "Sono presenti in $1 esattamente $num_file file"
echo "Sono presenti in $1 esattamente $num_dir directory"


