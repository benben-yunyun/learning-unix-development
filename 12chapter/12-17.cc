#include <iostream>
#include <unistd.h>

#if defined(_POSIX_THREADS)
#include <pthread.h>
#else
#pragma message("NOT SUPPORTED pthread")
#endif

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void)
{
    int err;
    std::cout << "preparing locks..." << std::endl;
    if (pthread_mutex_lock(&lock1)!=0) {
        exit(-1);
    }
    if (pthread_mutex_lock(&lock2)!=0) {
        exit(-1);
    }
}
void parent(void)
{
    std::cout << "parent unlocking locks...\n";
    if (pthread_mutex_unlock(&lock1)!=0) {
        exit(-1);
    }
    if (pthread_mutex_unlock(&lock2)!=0) {
        exit(-1);
    }
}

void child(void)
{
    std::cout << "child unlocking locks..." << std::endl;
    if (pthread_mutex_unlock(&lock1)!=0) {
        exit(-1);
    }
    if (pthread_mutex_unlock(&lock2)!=0) {
        exit(-1);
    }
}

void * thr_fn(void *arg)
{
    std::cout << "thread starteed..." << std::endl;
    pause();
    return(0);
}

int main(int argc, char *argv[])
{
    int err;
    pid_t pid;
    pthread_t tid;
    if (pthread_atfork(prepare,parent,child)!=0) {
        exit(-1);
    }
    if (pthread_create(&tid,NULL,&thr_fn,0)!=0) {
        exit(-1);
    }
    sleep(2);
    std::cout << "parent about to fork..." << std::endl;
    if ((pid = fork())<0) {
        exit(-1);
    }
    else if (pid == 0) {
        std::cout << "child returned from fork\n";
    }
    else {
        sleep(2);
        std::cout << "parent returned from fork\n";
    }
    return 0;
}
