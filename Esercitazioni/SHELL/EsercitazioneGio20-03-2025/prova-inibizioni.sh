#!/bin/sh
#file prova-inibizioni.sh

a=ciao 			#assegno alla variabile a la stringa ciao
#visualizziamo su standard output (N.B. con un unico comando echo) il valore della variabile a, della esecuzione del comando pwd e del metacarattere ASTERISCO
echo Valore della variabile a = $a, valore della dir corrente = `pwd` e valore di ASTERISCO = * 	
#N.B. In questo caso abbiamo usato all'interno del comando echo l'esecuzione del comando pwd perche' il testo dell'esercizio lo richiedeva!
#PROCEDIAMO CON LA INIBIZIONE DI TUTTE LE SOSTITUZIONI, sempre usando il comando echo: si devono usare le singole virgolette!
echo 'Valore della variabile a = $a, valore della dir corrente = `pwd` e valore di ASTERISCO = *' 	
#ORA PROCEDIAMO CON LA INIBIZIONE SOLO DELL'ULTIMA SOSTITUZIONE, sempre usando il comando echo: si devono usare le doppie virgolette!
echo "Valore della variabile a = $a, valore della dir corrente = `pwd` e valore di ASTERISCO = *" 	
