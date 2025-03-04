/* FILE: prova.c */
#include <stdio.h>	/* per usare scanf e printf */

int main()
{
	char c;		/* variabile per memorizzare i caratteri letti via via dallo standard input */

while (scanf("%c", &c) != EOF)	/* lettura di singoli caratteri dallo standard input, fino all'eof dello standard input */
	printf("%c", c);	/* scrittura dei caratteri letti sullo standard output */

return 0;
}
