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

void stampaNEsimoCarattereInFileConlseek(const char* F, int n){
        int fd;
        if((fd = open(F, O_RDONLY)) < 0){
            printf("Errore: impossibile aprire il file %s\n", F);
            exit(4);
        }
        long lunghezzaF = lseek(fd, 0, SEEK_END);
        char c;
        for(long i=n-1;i-1<lunghezzaF;i+=n){
            lseek(fd, (int)i, SEEK_SET);
            if(read(fd, &c, 1) == -1){
                printf("Errore durante la lettura del file\n");
                exit(5);
            }
            printf("Il carattere multiplo %d-esimo all'interno del file %s e' %c\n", n,F,c);
        }
        close(fd);
    }

int main(int argc, char* argv[]) {
    
    //Controllo esatto parametri
    int parametri = 2;
    if(argc != parametri+1){
        printf("Errore: inserire esattamente  PARAMETRI parametri, argc = %d\n", argc);
        exit(1);
    }

    //Controllo se e' un file
    char *F = argv[1];
    if( open(F, O_RDONLY) < 0){
        printf("Errore: il parametro %s non e' un file\n", F);
        exit(2);
    }

    //Controllo se e' un numero
    int n = atoi(argv[2]);
    if(n <= 0){
        printf("Errore: il parametro %s non e' un numero positivo\n", argv[2]);
        exit(3);
    }

    stampaNEsimoCarattereInFileConlseek(F, n);

    exit(0);
}