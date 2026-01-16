#include <stdio.h>


int main(int argc, char** argv)
{
    if( argc < 2)
    {
        return 1;
    }
    int N = argc - 1;
    printf("il nome dell'eseguibile : %s\n", argv[0]);
    printf("i valori passati sono: %d\n", N);

    for(int i = 1; i <= N; i++)
    {
        printf("%d)\t  %s\n", i, argv[i]);
    }
    
    return 0;
    
}
