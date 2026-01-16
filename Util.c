#include <stdio.h>     // importante per le stampe
#include <stdlib.h>    // per le calloc/malloc
#include <unistd.h>    // fork, pipe, read, write, close
#include <sys/wait.h>  // wait
#include <fcntl.h>     // modalità apertura file (O_RDONLY ecc..)
#include <string.h>    // per le stringhe
#include <signal.h>    // per i segnali
#include <time.h>      // per i random ( srand(time(NULL)) )
#include <ctype.h>     // per capire se un dato carattere è lettera o cifra
#include <stdbool.h>   // per boolean
typedef int pipe_t[2]; // pipe_t è per le pipe

/**
 * @brief Questa funzione ritorna un intero se è valido ed è compreso tra min e max inclusi
 *
 * @param str Stringa dove leggere l'intero
 * @param min Valore minimo che può assumere il numero
 * @param max Valore massimo che può assumere il numero
 * @param err_code In caso di errore verrà fatta la exit con questo codice
 * @return Numero compreso tra min e max letto da str
 */
int checkNumero(char *str, int min, int max, int err_code)
{
    int n = atoi(str);
    if (n < min || n > max)
    {
        printf("Il parametro '%s' non è un numero compreso tra %d e %d\n", str, min, max);
        exit(err_code);
    }
    return n;
}

/**
 * @brief Questa funzione ritorna il carattere se str è una stringa valida
 *
 * @param str Stringa dove controllare se è presente un singolo carattere
 * @param err_code In caso di errore verrà fatta la exit con questo codice
 * @return Carattere letto da str
 */
char checkChar(char *str, int err_code)
{
    if (str[1] != 0)
    {
        printf("Il parametro '%s' non è un singolo carattere\n", str);
        exit(err_code);
    }
    return str[0];
}

/**
 * @brief Ritorna l'indice della posizione di pid in pids
 *
 * @param pids Vettore di pid
 * @param N Dimensione del vettore pids
 * @param pid Pid da cercare dentro al vettore pids
 * @return indice del pid in pids
 */
int IndexOf(int *pids, int N, int pid)
{
    int ris = -1;
    for (int i = 0; i < N; i++)
    {
        if (pids[i] == pid)
        {
            ris = i;
            break;
        }
    }
    return ris;
}

char buffer[BUFSIZ];

/**
 * @brief Questa funzione apre un file col nome specificato come primo parametro in lettura
 *
 * @param filename Nome del file da aprire
 * @param err_code In caso di errore verrà fatta la exit con questo codice
 * @return File descriptor del file aperto correttamente usando O_RDONLY
 */
int apriFileLettura(char *filename, int err_code)
{
    int fd;
    if ((fd = open(filename, O_RDONLY)) < 0)
    {
        printf("Errore nell'apertura del file '%s'\n", filename);
        exit(err_code);
    }
    return fd;
}

/**
 * @brief Questa funzione apre un file col nome specificato come primo parametro in lettura e scrittura
 *
 * @param filename Nome del file da aprire
 * @param err_code In caso di errore verrà fatta la exit con questo codice
 * @return File descriptor del file aperto correttamente usando O_RDONLY
 */
int apriFileLetturaScrittura(char *filename, int err_code)
{
    int fd;
    if ((fd = open(filename, O_RDWR)) < 0)
    {
        printf("Errore nell'apertura del file '%s'\n", filename);
        exit(err_code);
    }
    return fd;
}

/**
 * @brief Questa funzione legge una linea dal file specificato da fd
 *
 * @param fd File Descriptor del file da dove si vuole leggere
 * @return Lunghezza della linea letta
 */
int readLine(int fd)
{
    int dim = 0;
    while (read(fd, buffer + dim, 1))
    {
        dim++;
        if (buffer[dim - 1] == '\n')
        {
            break;
        }
    }
    if (dim != 0)
    {
        buffer[dim] = 0;
    }
    return dim;
}

/**
 * @brief Questa funzione conta le occorrenze di Cx all'interno di str
 *
 * @param str Stringa dove fare la ricerca
 * @param Cx Carattere da cercare
 * @return Numero di occorrenze di Cx in str
 */
int countOccorrenze(char *str, char Cx)
{
    int ris = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == Cx)
        {
            ris++;
        }
    }
    return ris;
}

/**
 * @brief Questa funzione ritorna la posizione all'interno del file della prima occorrenza
 * del carattere Cx a partire da dove si trova attualmente nel file
 *
 * @param fd File descriptor del file dove eseguire la ricerca
 * @param Cx Carattere da cercare
 * @return long int che rapprensenta la posizione del carattere nel file, può essere -1L se non è presente il carattere
 */
long int prossimaOccorrenza(int fd, char Cx)
{
    long int ris = -1L;
    char ch;
    while (read(fd, &ch, 1))
    {
        if (ch == Cx)
        {
            ris = lseek(fd, 0L, SEEK_CUR) - 1;
            break;
        }
    }
    return ris;
}
