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

//devo generare dei processi per ogni file, i quali contano le occorrenze dei caratteri della stringa S che sono all'interno dei file e le manda al padre che manda in output il file, il pid, carattere: %c, numero: %d ... per ogni carattere

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */

//Ritorna il numero di occorrenze del carattere Cx nel file F
long int contaOccorrenzeCarattere(const char *F, char Cx){
    //Apertura file
    int fd, n;
    if((fd = open(F, O_RDONLY)) < 0){
        printf("Errore: impossibile aprire il file %s\n", F);
        exit(5);
    }
    char buffer;
    long int occorrenze = 0;
    //Lettura file carattere per carattere
    while((n = read(fd, &buffer, 1)) > 0){
        if(buffer == Cx){
            occorrenze++;
        }
    }
    printf("Il carattere %c compare %ld volte nel file %s\n", Cx, occorrenze, F);
    close(fd);
    return occorrenze;
}


int main(int argc, char const *argv[])
{
    /* code */
    //Controllo esatto parametri
    if(argc < 3 )
    {
        printf("Errore: inserire almeno 2 parametri, argc = %d\n", argc);
        exit(1);
    }
    


    int L = strlen(argv[1]);
   
    
    /* -------- Variabili locali ---------- */
    int pid;                			/* process identifier per le fork() */
    int N;                  			/* numero di file passati sulla riga di comando (uguale al numero di file) */
    pipe_t *piped;          			/* array dinamico di pipe descriptors per comunicazioni figli-padre  */
    int i, j;               			/* indici per i cicli */
    int pidWaitedSon, status, ritorno;	/* per valore di ritorno dei vari processi (figli/nipoti) */

    
        /* ------------------------------------ */
    
    N = argc - 1;

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(piped = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(2);
    }

    /* Inizializzo l'array delle pipe */
    for(i = 0; i < N; i++) {
        if(pipe(piped[i]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe, si è bloccato alla pipe di indice: %d!\n", i);
            exit(3);
        }
    }

   
    /* Creo N processi figli */
    for(i = 0; i < N; i++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", i);
            exit(4);
        }

        /* Codice del processo figlio */
        if(pid == 0) {

            /* Chiudo tutte le pipe di non interesse */
            for(j = 0; j < N; j++) {
                close(piped[j][0]);
                if(i != j)
                    close(piped[j][1]);
            }

            /*###############son operation###################*/
            
            //Conto le occorrenze di ogni carattere della stringa S nel file argv[i+2]
            for(j = 0; j < L; j++){
                long int occorrenze = contaOccorrenzeCarattere(argv[i+2], argv[1][j]);
                //Mando al padre il carattere e il numero di occorrenze
                write(piped[i][1], &argv[1][j], sizeof(char));    
                write(piped[i][1], &occorrenze, sizeof(long int));
            }

            exit(0); /* return del figlio al padre */
        }
        }
    
        /* Codice del processo padre */
    
        /* Chiudo tutte le pipe di non interesse */
        for(i = 0; i < N; i++) {
            close(piped[i][1]);
        }
        
    
    
    
        

        /*###############father operation###################*/
        //Leggo dai figli i caratteri e le occorrenze e stampoo
        /* Il padre aspetta i figli salvando lo status */

        
        for (i = 0; i < N; i++) {
            char carattere;
            long int occorrenze;
            read(piped[i][0], &carattere, sizeof(char));
            read(piped[i][0], &occorrenze, sizeof(long int));
            printf("%s %c: %ld\n", argv[i + 2], carattere, occorrenze);
            
        }
        if ((pidWaitedSon = wait(&status)) < 0) {
                printf("Errore in wait per il figlio %d-esimo!\n", i);
                exit(5);
            }
            if ((status & 0xFF) != 0)
                printf("Figlio %d-esimo con pid %d terminato in modo anomalo\n", i, pidWaitedSon);
            else {
                ritorno = (int)((status >> 8) & 0xFF);
                printf("Figlio %d-esimo con pid %d terminato correttamente con valore di ritorno %d\n", i, pidWaitedSon, ritorno);

                exit(0); /* return del padre al sistema */
            }
        }
            
    
        
    
