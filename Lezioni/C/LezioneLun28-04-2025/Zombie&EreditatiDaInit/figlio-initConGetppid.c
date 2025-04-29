/* Programma in C figlio-initConGetppid.c che non ha bisogno di parametri e mostra l'uso della primitiva fork per la creazione di un processo figlio; in questo caso, il padre termina senza aspettare il figlio e il figlio termina subito e il padre prima di fare la wait si mette in attesa di un dato che deve fornire l'utente, per poter verificare che il processo figlio viene ereditato dal processo init (PID=1)! */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
    int pid;      	/* pid per fork */
    int n;              /* per valore letto dal figlio */

	/* si genera un processo figlio */
	if ((pid = fork()) < 0)
	{ 	/* fork fallita */
		printf("Errore in fork\n");
		exit(1);
	} 
	
	if (pid == 0) 
	{ 	/* figlio */ 
		printf("Esecuzione del figlio %d con padre %d\n", getpid(), getppid()); 
		/* per fare in modo che il figlio non termini subito gli facciamo aspettare un dato che deve essere fornito dall'utente */
		/* potevamo usare anche una sleep, ma in questo modo possiamo tenere più sotto controllo la situazione */
		printf("Fornisci un valore intero\n"); 
		scanf("%d", &n);
		printf("Numero letto dal figlio %d\n", n); 
		printf("Valore di ppid dopo sicura morte del padre originale %d\n", getppid()); 
		exit(5); /* abbiamo usato lo stesso valore di prima, ma il padre non lo recupera perche' NON esegue la wait */
	}

	/* padre */
	printf("Sono il padre con pid %d e ho generato il figlio %d. BYE BYE!!!\n", getpid(), pid); 
	/* il padre termina senza fare la wait del figlio! */

	exit(0);
} 
