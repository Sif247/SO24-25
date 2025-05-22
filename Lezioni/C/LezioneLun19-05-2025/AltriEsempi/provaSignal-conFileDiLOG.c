/* Programma in C provaSignal-conFileDiLOG.c che si comporta come provaSignal.c, ma in cui la funzione catchint scrive su un file di log, denomicato sig.log */
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
   int fd;
   char s[100] = "Segnale nro  ";
   char s1[5];
   char s2[] = " e count = ";
   char s3[] = " ricevuto dal processo ";
   static int count = 0;  /* variabile contatore definita static e quindi allocata non nello stack, ma nei dati globali che hanno tempo di vita pari a quella del programma e quindi del processo! */

 	/* NON si disabilita il segnale SIGINT: dato che abbiamo verificato che il sistema che si sta usando si riferisce alla semantica BSD */
	sprintf(s1, "%d", signo);
	strcat(s, s1);
	strcat(s, s2);
	count++;
	sprintf(s1, "%d", count);
	strcat(s, s1);
	sprintf(s1, "%d", getpid());
	strcat(s, s3);
	strcat(s, s1);
	strcat(s, "\n");
	/* viene usato un file di nome sig.log (che creeremo/azzereremo dalla shell) per memorizzare le informazioni relative al numero del segnale e al contatore */
	if ((fd = open("sig.log", O_WRONLY)) < 0) exit(1);	/* se non si riesce ad aprire in sola scrittura il file, usciamo con errore */
	lseek(fd, 0L, 2);	/* se la open ha avuto successo, spostiamo l'I/O pointer alla fine in modo da appendere la stringa che abbiamo 'costruito' */
	/* se nota, si puo' usare anche la versione estesa della open che apre il file in APPEND */
	write(fd, s, strlen(s));
 	/* non si prevedono azioni di terminazione: ritorno al segnalato, SENZA BISOGNO DI RIPRISTINARE la catch function sempre secondo la semantica BSD */
}
