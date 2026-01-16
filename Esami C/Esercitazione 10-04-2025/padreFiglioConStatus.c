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
#include <time.h>

int mia_random(int n)
{
    int casuale;
    casuale = rand() % n;
    return casuale;
}


int main(int argc, char const *argv[])
{
    int pid;
    printf("Sono il processo padre con pid %d\n", getpid());
    srand(time(NULL));

    if((pid = fork()) < 0)
    {
        printf("Errore nella fork\n");
        exit(1);
    }
    if(pid == 0)
    {
        //Processo figlio
        int status;
        int random = mia_random(100);
        printf("Sono il processo figlio con pid %d e il mio processo padre è:  %d\n", getpid(), getppid());
        printf("DEBUG-Sono il figlio e sto per tornare al padre il valore %d\n", random);
        exit(random);
    }

    //Processo padre
    int status;
    int pidFiglio;
    int ritorno;
    /* il padre aspetta il figlio */
	if ((pidFiglio=wait(&status)) < 0)
	{
	        printf("ERRORE nella wait %d\n", pidFiglio);
	        exit(2);
	}
    else
	{
	        if (WIFEXITED(status))  
            {
                ritorno = WEXITSTATUS(status);
            }           

	        printf("Il figlio con pid=%d ha ritornato %d\n", pidFiglio, ritorno);
	}

	exit(0);
    
}
