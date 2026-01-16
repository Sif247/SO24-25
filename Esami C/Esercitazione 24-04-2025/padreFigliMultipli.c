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

int main(int argc, char* argv[]) 
{
    
    //Controllo esatto parametri
    if(argc != 2){
        printf("Errore: inserire esattamente 1 parametro, argc = %d\n", argc);
        exit(1);
    }

    //Controllo se e' un numero
    int n = atoi(argv[1]);
    if(n <= 0 || n >= 255){
        printf("Errore: il parametro %s non e' un numero positivo\n", argv[1]);
        exit(2);
    }

    printf("pid padre: %d\n", getpid());
    printf("valore N: %d\n", n);

    int pid;
    for (int i = 0; i < n; i++)
    {
        pid = fork();
    
        if(pid < 0)
        {
            printf("Errore nella fork\n");
            exit(3);
        }
        if(pid == 0)
        {
            printf("%d)\t pid: %d  padre: %d\n", i, getpid(), getppid());
            exit(i);
        }
    }

    exit(0);
}