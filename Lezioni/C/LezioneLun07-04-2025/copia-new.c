/* Programma in C copia-new.c che e' sostanzialmente una copia del programma in C copia.c */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 	/* per poter usare, oltre che la primitiva close, anche read e write */
#include <fcntl.h>
#define PERM 0666      	/* in ottale per diritti UNIX: read-write per TUTTI! */
/* rispetto al file copia.c abbiamo cambiato SOLO i permessi: peccato che se il comando umask riporta come nel nostro caso
soELab@lica04:~/file$ umask
0022
il risultato e' comunque che il file viene creato con i diritti rw per U, e r per G e O e quindi 0644.
Vediamo perche'.  Dal manuale della open/creat scopriamo che:
The effective permissions are modified by the process's umask in the usual way: The permissions of the created file are (mode & ~umask)
Quindi se mode = 0666 e umask = 0022, tralasciando lo 0 iniziale abbiamo che
666 in binario e' 10110110 e 022 e'¨ 000010010 e quindi ~umaske'¨ 111101101 e quindi mode & ~umk e'
  110110110 &
  111101101
  =========
  110100100
  e quindi proprio 644 */

int main (int argc, char** argv)
{    
     	int infile, outfile, nread;	/* usati per open e valore ritorno read */
     	char buffer[BUFSIZ];  		/* usato per i caratteri, letti dal file sorgente e scritti sul file destinazione */

	if (argc != 3)  /* controllo sul numero di parametri: devono essere esattamente 2! */
     	{ 	printf("Errore: numero di argomenti sbagliato dato che argc = %d\n", argc);
       		printf("Ci vogliono 2 argomenti: nome-file-sorgente e nome-file-destinazione\n");
       		exit(1); 
	}

	/* se si arriva qui, sono stati passati esattamente 2 parametri */

	/* tentiamo l'apertura in lettura del file il cui nome e' stato passato come primo parametro */
	if ((infile = open(argv[1], O_RDONLY)) < 0) 
	/* ERRORE se non si riesce ad aprire in LETTURA il primo file */
	{       printf("Errore in apertura file per %s dato che infile = %d\n", argv[1], infile);
		exit(2);
	}

	/* tentiamo la creazione del file il cui nome e' stato passato come secondo parametro */
	if ((outfile = creat(argv[2], PERM)) < 0 )
	/* ERRORE se non si riesce a creare il secondo file */
	{       printf("Errore nella creazione file per %s dato che outfile = %d\n", argv[2], outfile);
		exit(3);
	}

	/* se si arriva qui, e' stato aperto il primo file in lettura ed e' stato creato il secondo file */
	/* procediamo quindi con la lettura dal primo file e la scrittura sul secondo, fino a che ci sono byte nel primo file */
	while ((nread = read(infile, buffer, BUFSIZ)) > 0 )	/* ciclo di lettura fino a che nread e' maggiore di 0; FARE MOLTA ATTENZIONE ALLE PARENTESI INDICATE! */
	{ 
		if (write(outfile, buffer, nread) < nread)	/* scriviamo sempre nread byte! */
		/* ERRORE se non si riesce a SCRIVERE; N.B. questa eventualita' si potra' NON considerarla */
		{       printf("Errore nella scrittura del file per %s\n", argv[2]);
			exit(4);
		}
	}	

	/* se arriviamo qui, vuol dire che tutto e' andato bene */
	exit(0);
}
