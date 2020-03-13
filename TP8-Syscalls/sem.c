//
// Created by pauldance on 13/03/2020.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>


int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Expected one argument.\n");
		return 1;
	}
	
	unsigned short number = strtoul(argv[1], NULL, 0);
	sem_t* sem = sem_open("/sync", O_CREAT, S_IRWXU, 4);
	sem_unlink("/sync");
	
	for (unsigned short i = 0; i < number; i++) {
		fork();
	}
	
	sem_wait(sem);
	printf("[%d] says hello.\n", getpid());
	sleep(1);
	printf("[%d] says bye.\n", getpid());
	sem_post(sem);
	sem_destroy(sem);
}
