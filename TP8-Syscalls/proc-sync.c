#include <stdio.h>
#include <unistd.h>

#define SYNC_FILE "sync"
int watch = 42;


int main() {
    const pid_t childPid = fork();

    if (childPid == 0) {
        printf("Hhh hhh no, no!\n");
        printf("Instruction block B1: before.\n");

        watch = 666;
        printf("PID: %i, &watch: %p, watch: %i\n", getpid(), &watch, watch);

        fopen(SYNC_FILE, "w+");
    } else {
        printf("I am your father.\n");
        FILE *syncFile = NULL;

        while ((syncFile = fopen(SYNC_FILE, "r")) == NULL) {
            usleep(10000);
        }

        fclose(syncFile);
        unlink(SYNC_FILE);
        printf("Instruction block B2: after.\n");
        printf("PID: %i, &watch: %p, watch: %i\n", getpid(), &watch, watch);
    }

    return 0;
}
