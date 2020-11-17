#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define N 5000


static volatile size_t nb_sigs = 0;
static volatile unsigned long long k = 0;

void hello(int sig) {
    if (nb_sigs % 1000 == 0) {
        printf("Hello %i\n", sig);
    }

    k--;
    nb_sigs++;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = &hello;
    sigaction(SIGALRM, &sa, NULL);
    unsigned long long ref = 0;

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);

    while (nb_sigs != N) {
        ualarm(1, 0);
        usleep(1);

        sigprocmask(SIG_BLOCK, &set, NULL);
        k++;
        sigprocmask(SIG_UNBLOCK, &set, NULL);
        ref++;
    }

    printf("ref - k = %llu\n", ref - k);
}
