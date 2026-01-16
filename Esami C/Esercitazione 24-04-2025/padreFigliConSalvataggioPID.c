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
    casuale++;
    return casuale;
}

int main(int argc, char const *argv[])
{
    //Controllo esatto parametri
    if(argc != 2){
        printf("Errore: inserire esattamente  1 parametri, argc = %d\n", argc);
        exit(1);
    }

    //Controllo se e' un numero
    int n = atoi(argv[1]);
    if(n <= 0){
        printf("Errore: il parametro %s non e' un numero positivo\n", argv[1]);
        exit(2);
    }
    else if (n >= 155)
    {
        printf("Errore: il parametro %s non e' un numero maggiore di 154\n", argv[1]);
        exit(3);
    }

    printf("pid padre: %d\n", getpid());
    printf("valore N: %d\n", n);

    int pid;
    int random;
    /* ARRAY PER SALVARE I PID */
    pid_t *pidFigli = malloc(n * sizeof(pid_t));
    if (pidFigli == NULL) {
        perror("malloc");
        exit(4);
    }

    srand(time(NULL));
    
    
    //figli
    for (int i = 0; i < n; i++)
    {
        
        pid = fork();
        if(pid < 0)
        {
            printf("Errore nella fork\n");
            exit(5);
        }
        if(pid == 0)
        {
            random = mia_random(100 + i);
            printf("%d)\tpid: %d\n", i, getpid());
            exit(random);
        }

        pidFigli[i] = pid;
    }
    


    //padre
    int pidFiglio, status, ritorno;

    /* Il padre aspetta i figli salvando lo status */
    for (int i = 0; i < n; i++) {
        if ((pidFiglio = wait(&status)) < 0) 
        {
            printf("Errore in wait\n");
            exit(6);
        }


        ritorno = (status >> 8) & 0xFF;

        /* cerco l'indice */
        int indice = -1;
        for (int j = 0; j < n; j++) {
            if (pidFigli[j] == pidFiglio) {
                indice = j;
                break;
            }
        }

        printf("Figlio P%d (pid=%d) ha ritornato %d\n",
               indice, pidFiglio, ritorno);
    }

    
    exit(0);
}
