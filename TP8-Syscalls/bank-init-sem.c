//
// Created by pauldance on 13/03/2020.
//

#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Expected 1 arguments: a semaphore name, slash included.\n");
        return 1;
    }

    sem_t *sem = sem_open(argv[1], O_CREAT, S_IRWXU, 1);
    //sem_destroy(sem);

    return 0;
}
