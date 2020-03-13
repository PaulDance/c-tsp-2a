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


int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "Expected 2 arguments: a name and a number.\n");
		return 1;
	}
	
	char* name = argv[1];
	double money = strtod(argv[2], NULL);
	double balance;
	
	//sem_t* sem = sem_open("/bank", O_CREAT, S_IRWXU, 1);
	sem_t* sem = sem_open("/bank", O_RDONLY);
	fprintf(stderr, "[%i] %p - error: %s\n", getpid(), sem, strerror(errno));
	
//	if (sem == SEM_FAILED) {
//		fprintf(stderr, "[%i] ", getpid());
//		perror("error");
//		
//		if (errno == EEXIST) {
//			fprintf(stderr, "[%i] open no create\n", getpid());
//			sem = sem_open("/bank", O_RDONLY);
//			fprintf(stderr, "[%i] %p\n", getpid(), sem);
//			//perror("error");
//		}
//	}
	
	sem_wait(sem);
	FILE* file = fopen(name, "r");
	
	if (file != NULL) {
		fread(&balance, sizeof(balance), 1, file);
		fclose(file);
	}
	else {
		balance = 0.0;
	}
	
	balance += money;
	fprintf(stderr, "[%i] Name: %s, balance: %lf\n", getpid(), name, balance);
	
	file = fopen(name, "w+");
	fwrite(&balance, sizeof(balance), 1, file);
	fclose(file);
	
	sem_post(sem);
	sem_destroy(sem);
	sem_unlink("/bank");
}
