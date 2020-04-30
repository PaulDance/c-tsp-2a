//
// Created by pauldance on 13/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Expected 2 arguments: a name and a number.\n");
        return 1;
    }

    char *name = argv[1];
    double money = strtod(argv[2], NULL);
    double balance;

    sem_t *sem = sem_open("/bank", O_CREAT, S_IRWXU, 1);
    printf("[%i] %p - sem error: %s ", getpid(), sem, strerror(errno));

    if (sem == SEM_FAILED) {
        printf("(failure)\n");
    } else {
        printf("(ok)\n");
    }

    int semCurVal;
    sem_getvalue(sem, &semCurVal);
    printf("[%i] %p - sem value: %i\n", getpid(), sem, semCurVal);

    if (semCurVal != 0) {
        printf("[%i] %p - sem wait.\n", getpid(), sem);
        sem_wait(sem);
    } else {
        printf("[%i] %p - sem no wait.\n", getpid(), sem);
    }

    FILE *file = fopen(name, "r+");
    printf("[%i] %p - file error: %s\n", getpid(), sem, strerror(errno));

    if (file != NULL) {
        fread(&balance, sizeof(balance), 1, file);
        fclose(file);
    } else {
        balance = 0.0;
    }

    balance += money;
    printf("[%i] Name: %s, balance: %lf\n", getpid(), name, balance);

    file = fopen(name, "w");
    fwrite(&balance, sizeof(balance), 1, file);
    fclose(file);

    sem_post(sem);
    sem_destroy(sem);
    sem_unlink("/bank");
}
