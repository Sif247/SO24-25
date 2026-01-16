#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>  // per atoi
#include <fcntl.h>   // per open
#include <unistd.h>  // per close


int main ( int argc, char** argv )
{
    if(argc != 4)
    {
        printf("Errore: numero parametri sbagliato");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Errore: apertura file");
        return 1;
    }

    int N = atoi(argv[2]);

    if( N <= 0)
    {
        printf("Errore: %d deve essere positivo", N);
        return 1;
    }

    
    if (strlen(argv[3]) != 1)
    {
        printf("Errore: la variabile C deve avere un solo carattere");
        return 1;
    }
    char C = argv[3][0];

    
    printf("Nome file:\t parametri2.c\n");
    printf("il numero di parametri è %d\n", argc -1 );

    printf("Nome file:\t %s \n", argv[1]);
    printf("Valore numero intero:\t %d \n", N);
    printf("Valore carattere:\t %c \n", C);

    return 0;
    
    
}