#include <stdio.h>	   // importante per le stampe
#include <stdlib.h>	   // per le calloc/malloc
#include <unistd.h>	   // fork, pipe, read, write, close
typedef int pipe_t[2]; // pipe_t è per le pipe
typedef enum
{
	READER = 0,
	WRITER = 1
} ROLE;

/**
 * @brief Questa funzione alloca dinamicamente un vettore di N pipe e gestisce il caso di memoria non valida
 *
 * @param N Dimensione del vettore da creare
 * @param name Nome della pipe da stampare in caso di errore, per avere migliore leggibilità
 * @param err_code In caso di errore verrà fatta la exit con questo codice
 * @return pipe_t* piped allocata e settata
 */
pipe_t *creaPipe(int N, char *name, int err_code)
{
	pipe_t *piped = calloc(N, sizeof(pipe_t));
	if (piped == NULL)
	{
		printf("Errore nella calloc della '%s'\n", name);
		exit(err_code);
	}
	for (int i = 0; i < N; i++)
	{
		if (pipe(piped[i]) < 0)
		{
			printf("Errore nella primitiva pipe\n");
			exit(err_code);
		}
	}
	return piped;
}

/**
 * @brief Questa funzione chiude tutti i canali della pipe che non sono utilizzati
 *      dal processo figlio ad esclusione della pipe 'piped[index][role]'
 *
 * @param piped Vettore che rappresenta N pipe_t già settati
 * @param N La dimensione del vettore piped
 * @param index Indice nel vettore di pipe che non voglio chiudere
 * @param role Ruolo che ha il processo figlio nella pipe selezionata, READER o WRITER
 */
void pipeCloseExcept(pipe_t *piped, int N, int index, ROLE role)
{
	for (int i = 0; i < N; i++)
	{
		close(piped[i][1 - role]);
		if (i != index)
		{
			close(piped[i][role]);
		}
	}
}

/**
 * @brief Questa funzione chiude tutti i canali della pipe che non sono utilizzati
 *      dal processo figlio ad esclusione delle pipe 'piped[indexR][READER]' e
 *      'piped[indexW][WRITER]'
 *
 * @param piped Vettore che rappresenta N pipe_t già settati
 * @param N La dimensione del vettore piped
 * @param indexR Indice nel vettore di pipe che non voglio chiudere per il canale READER
 * @param indexW Indice nel vettore di pipe che non voglio chiudere per il canale WRITER
 */
void pipeLine(pipe_t *piped, int N, int indexR, int indexW)
{
	for (int i = 0; i < N; i++)
	{
		if (i != indexR)
		{
			close(piped[i][READER]);
		}
		if (i != indexW)
		{
			close(piped[i][WRITER]);
		}
	}
}

int main(int argc, char *argv[])
{
	int pid;
	int N = 5;
	pipe_t *fp = creaPipe(N, "pipe figlio-padre", 1);
	pipe_t *pf = creaPipe(N, "pipe padre-figlio", 2);

	for (int i = 0; i < N; i++)
	{
		if ((pid = fork()) < 0)
		{
			printf("Errore nella fork!\n");
			exit(3);
		}
		if (pid == 0) // figlio
		{
			// chiudo tutti i canali non usati nella pipe tranne piped[i] lato WRITER
			pipeCloseExcept(fp, N, i, WRITER);
			// chiudo tutti i canali non usati nella pipe tranne piped[i] lato READER
			pipeCloseExcept(pf, N, i, READER);

			// altre operazioni

			exit(0);
		}
		else
		{
			printf("Creato il figlio #%d associato al file '%s'\n", pid, argv[i + 1]);
		}
	}

	int pid, status;
	for (int i = 0; i < N; i++)
	{
		if ((pid = wait(&status)) < 0)
		{
			printf("Errore in wait\n");
			exit(5);
		}
		if (status % 256 != 0)
		{
			printf("Figlio #%d terminato in modo anomalo\n", pid);
		}
		else
		{
			status = (status >> 8) % 256;
			printf("Il figlio #%d ha ritornato %d\n", pid, status);
		}
	}

	exit(0);
}