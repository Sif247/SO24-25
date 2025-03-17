#!/bin/sh
x='ls -l $z'	#assegniamo un valore alla variabile x facendo uso dei singoli apici sia per inibire le sostituzioni (in questo caso la prima) e sia per inserire degli spazi!
z=provaSost.sh	#assegniamo un valore alla variabile z
$x		#vogliamo eseguire il comando rappresentato dal valore della variabile x
eval $x		#per ottenere il risulato complessivo dobbiamo usare il comando eval perche' la shell esegue solo una passata di sostituzioni e quindi bisogna forzarne un'altra in questo caso!
