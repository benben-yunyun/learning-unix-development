#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <cstdio>
void configure() {
#if defined _POSIX_THREADS
    std::cout << "_POSIX_THREADS configure" << std::endl;
#endif
}

pthread_t ntid;
void printids(const char * s) {
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n",s,(unsigned long )pid,(unsigned long)tid, (unsigned long)tid);
}

void * thr_fn(void *arg) {
    printids("new thread: ");
    return ((void*)0);
}



int main(int argc, char *argv[])
{
    int err;

    err = pthread_create(&ntid,NULL,thr_fn,NULL);
    if (err != 0) {
        printf("failure to create thread");
        exit(-1);
    }
    printids("main thread: ");
    sleep(1);
    return 0;
}
