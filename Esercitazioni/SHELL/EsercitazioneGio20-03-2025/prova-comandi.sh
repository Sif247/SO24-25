#!/bin/sh
#file prova-comandi.sh

echo Nome assoluto del file p.txt = `pwd`/p.txt #visualizziamo il nome assoluto del file p.txt usando la seconda sostituzione, quella del risultato di un comando, in questo caso, il pwd!
echo -n 'Directory corrente = '	#N.B. L'opzione -n serve per non andare a capo; abbiamo usato le singole virgolette per inserire lo spazio alla fine per non avere la stampa della dir corrente attaccata
pwd				#in questo caso il comando pwd e' stato usato in modo separato al comando echo!
echo -n "[Secondo-modo]Directory corrente = "	#facciamo la prova anche con le doppie virgolette che servono allo stesso scopo indicato sopra
pwd				#idem
