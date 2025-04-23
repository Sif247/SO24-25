/* Programma in C callecho.c che non ha bisogno di parametri e mostra l'uso della primitiva execvp  per la esecuzione dell'eseguibile myecho (che deriva dal programma in C myecho.c) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
  char *argin[4]; /* array statico di puntatori a char che serve per passare i parametri alla execvp */

	/* per prima cosa riempiamo l'array e quindi il VETTORE di stringhe che verra' usato nel comando execvp */
  	argin[0]="myecho";	/* argin[0] e' un puntatore a char cui viene assegnato il puntatore alla stringa "myecho" */
	argin[1]="hello"; 	/* argin[1] e' un puntatore a char cui viene assegnato il puntatore alla stringa "hello" */
	argin[2]="world!";	/* argin[2] e' un puntatore a char cui viene assegnato il puntatore alla stringa "world!" */
	argin[3]=(char *)0;	/* argin[3] e' un puntatore a char cui viene assegnato il valore 0 come puntatore a char */

	printf("DEBUG-Esecuzione di myecho\n");
	execvp(argin[0], argin);

	/* si esegue l'istruzione seguente SOLO in caso di fallimento della execvp */
	printf("Errore in execvp\n");
	exit(1);	 /* torniamo quindi un valore diverso da 0 per indicare che ci sono stati dei problemi */
}
