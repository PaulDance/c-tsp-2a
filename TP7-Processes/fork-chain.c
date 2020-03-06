//
// Created by pauldance on 06/03/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

const static unsigned short CHAIN_LENGTH = 10;


void forkChain(unsigned short length) {
	printf("Process: PID = %d, PPID = %d.\n", getpid(), getppid());
	const pid_t childPid = fork();
	
	if (childPid == 0) {
		if (length != 1) {
			forkChain(length - 1);
			wait(NULL);
		}
		else {
			printf("\n");
			execlp("ps", "ps", "f", NULL);
		}
	}
}


int main() {
	forkChain(CHAIN_LENGTH);
}
