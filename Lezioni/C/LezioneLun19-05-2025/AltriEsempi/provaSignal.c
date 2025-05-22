/* Programma in C provaSignal.c che non ha bisogno di parametri e mostra, di nuovo, un esempio del segnale SIGINT (che viene mandato dal kernel quando usiamo la combinazione di tasti CTRL-C), ma in questo caso, si AGGANCIA un'azione (diversa da quella di default) che, alla ricezione del SIGINT, fara' scrivere al proceso sullo stadard output delle informazioni e NON provochera' la terminazione del processo! */
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void catchint(int); /* prototipo/dichiarazione della funzione che rappresenta il gestore/handler del segnale SIGINT */

int main() 
{   
	/* agganciamo il segnale alla funzione gestore/handler di nome catchint */
	signal(SIGINT, catchint); 	/* N.B.: il nome di una funzione corrisponde al puntatore al suo codice */

	printf("Sono il processo %d\n", getpid());

	while (1)	/* ciclo infinito */
		;
}
 
void catchint(int signo)  /* alla funzione associata al segnale, il kernel passa il numero del segnale che l'attiva */
{ 
   static int count = 0;  /* variabile contatore definita static e quindi allocata non nello stack, ma nei dati globali che hanno tempo di vita pari a quella del programma e quindi del processo! */

   	count++;	/* incrementiamo il contatore */
 	/* NON si disabilita il segnale SIGINT: dato che abbiamo verificato che il sistema che si sta usando si riferisce alla semantica BSD */
	printf("Segnale nro = %d  e count = %d ricevuto dal processo con PID = %d\n", signo, count, getpid());
 	/* non si prevedono azioni di terminazione: ritorno al segnalato, SENZA BISOGNO DI RIPRISTINARE la catch function sempre secondo la semantica BSD */
}
