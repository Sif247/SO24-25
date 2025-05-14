#!/bin/sh
#file comandi DIR.sh

if [ "$#" -ne 1 ]; then
   echo "Errore, fornire esattamente un parametro"
   exit 1
fi

arg=$1

if [ -d $arg ]; then
   echo "E' una directory: " 
   ls -ld $arg
elif [ -f $arg ]; then 
     echo "E' un file: "
     ls -l $arg
else
     echo "Errore, non è ne un file ne una directory"
     exit 2
fi

