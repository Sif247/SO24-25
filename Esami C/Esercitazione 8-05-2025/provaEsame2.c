/* File provaEsame2.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */

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




int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc < 3) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s \n", argv[0]);
        exit(1);
    }

    

    /* -------- Variabili locali ---------- */
    int pid;                			/* process identifier per le fork() */
    int N;                  			/* numero di file passati sulla riga di comando (uguale al numero di file) */
    pipe_t *piped;          			/* array dinamico di pipe descriptors per comunicazioni figli-padre  */
    int i, j;               			/* indici per i cicli */
    int pidWaitedSon, status, ritorno;	/* per valore di ritorno dei vari processi (figli/nipoti) */          				/* file descriptor */
    long int ris;
    
    /* ------------------------------------ */

    /* Salvo il numero dei file in una variabile */
    N = argc - 2; 

    for (size_t i = 0; i < N; i++)
    {
        /* code */
        /* controllo che il XXXX parametro sia un singolo carattere */
        if (argv[i + 2][1] != '\0') {
            printf("Error: %s non singolo carattere\n", argv[i + 2]);
            exit(2);
        }
    }

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(piped = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(3);
    }

    /* Inizializzo l'array delle pipe */
    for(i = 0; i < N; i++) {
        if(pipe(piped[i]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe, si è bloccato alla pipe di indice: %d!\n", i);
            exit(4);
        }
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* Creo N processi figli */
    for(i = 0; i < N; i++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", i);
            exit(5);
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
            ris = contaOccorrenzeCarattere(argv[1], argv[i + 2][0]);
            write(piped[i][1], &ris, sizeof(ris));
            close(piped[i][1]);
            exit(argv[i + 2][0]);

        }
    }

    /* Codice del processo padre */

    /* Chiudo tutte le pipe di non interesse */
    for(i = 0; i < N; i++) {
        close(piped[i][1]);
    }
    
    /*###############father operation###################*/

    for (i = 0; i < N; i++) 
    {
        if(read(piped[i][0], &ris, sizeof(ris)) != sizeof(ris))
        {
            printf("Errore lettura dalla pipe %d\n", i);
            exit(6);
        }
        printf("Carattere: %c -> Occorrenze: %ld\n", argv[i + 2][0], ris);
        close(piped[i][0]);
    }


    /* Il padre aspetta i figli salvando lo status */
    for (i = 0; i < N; i++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", i);
            exit(5);
        }
        if ((status & 0xFF) != 0)
            printf("Figlio %d-esimo con pid %d terminato in modo anomalo\n", i, pidWaitedSon);
        else {
            ritorno = (char)((status >> 8) & 0xFF);
            printf("--------------------------\n");
            printf("DEBUG: Il figlio %d-esimo con pid=%d ha ritornato %c (se 255 problemi)\n", i, pidWaitedSon, ritorno);
            printf("--------------------------\n");
        }
    }

    exit(0); /* return del padre al sistema */
}