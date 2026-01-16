#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

typedef int pipe_t[2];

int main(int argc, char *argv[])
{
    int i, fd, pid;
    char c, ultimo = 0;
    int status;

    /* ===== CONTROLLI ===== */
    if (argc < 3) {
        printf("Errore: servono almeno 2 file\n");
        exit(1);
    }

    int N = argc - 1;

    /* ===== CREAZIONE PIPE ===== */
    pipe_t p[2];

    if (pipe(p[0]) < 0 || pipe(p[1]) < 0) {
        perror("pipe");
        exit(2);
    }

    /* ===== ARRAY PID ===== */
    pid_t pidFigli[N];

    /* ===== CREAZIONE FIGLI ===== */
    for (i = 0; i < N; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(3);
        }

        if (pid == 0) {  // FIGLIO
            close(p[0][0]);
            close(p[1][0]);

            fd = open(argv[i + 1], O_RDONLY);
            if (fd < 0) {
                perror("open");
                exit(4);
            }

            while (read(fd, &c, 1) > 0) {
                if ((i % 2 == 0) && isalpha(c)) {
                    write(p[1][1], &c, 1);
                    ultimo = c;
                }
                if ((i % 2 == 1) && isdigit(c)) {
                    write(p[0][1], &c, 1);
                    ultimo = c;
                }
            }

            close(fd);
            exit((unsigned char)ultimo);
        }

        pidFigli[i] = pid;
    }

    /* ===== PADRE ===== */
    close(p[0][1]);
    close(p[1][1]);

    int fineLettere = 0, fineNumeri = 0;
    int totale = 0;

    while (!fineLettere || !fineNumeri) {
        if (!fineLettere && read(p[1][0], &c, 1) > 0) {
            write(1, &c, 1);
            totale++;
        } else fineLettere = 1;

        if (!fineNumeri && read(p[0][0], &c, 1) > 0) {
            write(1, &c, 1);
            totale++;
        } else fineNumeri = 1;
    }

    printf("\nTotale caratteri scritti: %d\n", totale);

    /* ===== WAIT ===== */
    for (i = 0; i < N; i++) {
        pid = wait(&status);
        if ((status & 0xFF) == 0) {
            char r = (status >> 8) & 0xFF;
            printf("Figlio pid=%d ha ritornato '%c' (%d)\n",
                   pid, r, r);
        }
    }

    return 0;
}


