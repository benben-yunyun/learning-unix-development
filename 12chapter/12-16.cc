#include <iostream>
#include <unistd.h>

#if defined _POSIX_PTHREAD
#include <pthread.h>
#else
#pragma message("NOT SUPPORTED pthread")
#endif

#include <signal.h>

int quitflag;
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;

void * thr_fn(void * arg)
{
    int err, signo;
    while(true) {
        err = sigwait(&mask,&signo);
        if (err != 0) {
            exit(-1);
        }
        switch(signo) {
            case SIGINT: std::cout << "\ninterrupt\n"; break;
            case SIGQUIT:
                pthread_mutex_lock(&lock);
                quitflag = 1;
                pthread_mutex_unlock(&lock);
                pthread_cond_signal(&waitloc);
                return (0);
            default:
                std::cout << "unexpected signal " << signo << std::endl;
                exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    int err;
    sigset_t oldmask;
    pthread_t tid;

    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    sigaddset(&mask,SIGQUIT);

    if ((err=pthread_sigmask(SIG_BLOCK,&mask,&oldmask))!=0) {
        exit(-1);
    }
    if (pthread_create(&tid,NULL,thr_fn,0)!=0) {
        exit(-1);
    }

    pthread_mutex_lock(&lock);
    while (quitflag == 0) {
        pthread_cond_wait(&waitloc,&lock);
    }
    pthread_mutex_unlock(&lock);
    quitflag = 0;
    if (sigprocmask(SIG_SETMASK,&oldmask,NULL)<0) {
        exit(-1);
    }
    return 0;
}
