#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR, O_CREAT(crea se non esiste), O_APPEND(solo R o RW)
//O_TRUNC(distrugge contenuto se esiste, O_EXCL(fallisce se il file esiste gia'), O_NDELAY (non bloccante per FIFO e pipe in W)
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG
#include <sys/wait.h> //SYStem WAIT: wait
#include <errno.h> //ERror NUmber: errno
#include <sys/types.h> //SYStem TYPES: pid_t
#include <ctype.h> //ISoType: isdigit, isalpha, isalnum

int main(int argc, char const *argv[])
{
    
    int pidFiglio;  /* per valore di ritorno della wait */

	/* stampiamo quanto richiesto dal testo */
	printf("Sono il processo padre con pid %d\n", getpid());

	/* padre (!?!) */
        if ((pidFiglio=wait((int *)0)) < 0)	 /* in questo caso si e' usata la wait disinteressandoci del valore di ritorno dato che avremo errore! */
	/* nonostante questo processo non abbia creato figli, invoca la primitiva wait; chiaramente il codice potrebbe essere, 'a monte', molto piu' complicato e potrebbe essere NON chiaro il fatto che non e' stato creato alcun processo figlio: quindi bisogna sempre controllare il valore di ritorno della wait! */
	{
		printf("ERRORE nella wait %d\n", pidFiglio);
		exit(1);
	}
	
	exit(0);	/* chiaramente in questo caso NON si eseguira' mai questa istruzione, dato che si uscira' sempre con errore */
}