#Non abbiamo inserito lo shbang e questo comporta che nella esecuzione di questo script verra' usata la shell di partenza che nel mio caso è la bah
#file provaExit.sh

echo proviamo ad usare il comando exit con un numero negativo ad esempio -1
exit -1 	#verificare il valore presente al termine nella variabile $?
#Negli script che vedremo, pero', NON useremo mai dei numeri negativi, ma li useremo invece, in alcuni casi, per il valore di ritorno di processi figli in C e quindi vale la pena vedere cosa succede con un exit con valore negativo!
