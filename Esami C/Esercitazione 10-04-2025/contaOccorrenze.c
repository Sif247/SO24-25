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


//Ritorna il numero di occorrenze del carattere Cx nel file F
long int contaOccorrenzeCarattere(const char *F, char Cx){
    /* Apertura file in lettura */
    int fd = open(F, O_RDONLY);
    if (fd < 0) 
    {
    perror("Errore apertura file");
    exit(4);
    }   

    char c;
    long int occorrenze = 0;

    while(read (fd, &c, 1) > 0)
    {
        if(c == Cx)
        {
            occorrenze++;
        }
    }
    close(fd);

    return occorrenze;

}


int main(int argc, char const *argv[])
{
    int parametri = 2;
    //Controllo esatto parametri
    if(argc != parametri+1){
        printf("Errore: inserire esattamente  2 parametri, argc = %d\n", argc);
        exit(1);
    }

    //Controllo se e' un file
    if( open(argv[1], O_RDONLY) < 0){
        printf("Errore: il parametro %s non e' un file\n", argv[1]);
        exit(2);
    }
    char *F = argv[1];

    //Controllo se e' un carattere
    //ARRAY DI CARATTERI

    if(argv[2][1] != '\0'){
        printf("Errore: il parametro %s non e' un carattere\n", argv[2]);
        exit(3);
    }
    char Cx = argv[2][0];

    printf("nome eseguibile: %s\n", argv[0]);
    printf("nome file: %s\n", F);
    printf("il carattere da cercare è: %c\n", Cx );

    long int ris = contaOccorrenzeCarattere(F, Cx);
    printf("Il numero di occorrenze del carattere %c nel file %s è:   %ld\n", Cx, F, ris);

    return 0;
}
