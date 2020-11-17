#ifndef _POKEMON_H_
#define _POKEMON_H_

#include <stdio.h>       /* fopen, fprintf, fread, fscanf, fseek, ftell, fclose */
#include <string.h>      /* strcmp, strncpy */
#include <stdlib.h>      /* malloc, free, exit, atoi */
#include <unistd.h>      /* sleep, unlink, getpid */
#include <fcntl.h>       /* O_CREAT, S_IRWXU */
#include <semaphore.h>   /* sem_open, sem_unlink, sem_wait, sem_post */
#include <sys/wait.h>    /* wait */

#define POKEDEX "pokedex.dat"
#define SEM     "/pokemon"
#define MAXLEN  32

struct pokemon {
    int unused;
    char name[MAXLEN];
    char type[2][MAXLEN];
};

#endif
