/* Programma in C leggiPippo.c che non ha bisogno di parametri e ha come compito, dopo aver stampato Real-UID e Effective-UID di leggere il file pippo e di riportare tutti i caratteri sullo standard output */
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
 
int main()
{
   int fd;	/* per la open */
   char c;	/* per leggere i caratteri dal file pippo */

	printf("Real-user id = %d\n", getuid());
	printf("Effective-user id = %d\n", geteuid());
	printf("Sto per leggere il file pippo\n");

	if ((fd=open("pippo", O_RDONLY)) < 0) 
	{ 	printf("ERRORE in apertura\n");
		exit(1);
	}

	/* andiamo a leggere un carattere alla volta dal file pippo anche se a livello di prestazioni non e' la cosa piu' furba! */
	while(read(fd, &c, 1))
  		write(1, &c, 1);

	exit(0);
}
