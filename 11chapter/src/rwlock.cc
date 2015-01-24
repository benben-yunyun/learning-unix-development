#include <iostream>
#include <unistd.h>

#if defined _POSIX_THREADS
#include <pthread.h>
#else
#pragma message("not supported pthread")
#endif

static int count;
pthread_rwlock_t rdlock;

void * read_fn(void * arg) {
    for (;true;) {
        usleep(100);
        pthread_rwlock_rdlock(&rdlock);
        std::cout << "pthread:" << pthread_self() << "\tcount:" << count << std::endl;
        pthread_rwlock_unlock(&rdlock);
    }
}

void * write_fn(void * arg) {
    for (;true;) {
        sleep(1);
        pthread_rwlock_wrlock(&rdlock);
        count++;
        pthread_rwlock_unlock(&rdlock);
    }
}
void create_thread() {
    pthread_t read_thread1,read_thread2,write_thread;
    if (pthread_rwlock_init(&rdlock,nullptr)!=0) {
        std::cout << "failure to init the pthread rdlock" << std::endl;
        exit(-1);
    }
    count = 0;
    if (pthread_create(&read_thread1,nullptr,read_fn,nullptr)!=0) {
        std::cout << "failure to create read pthread" << std::endl;
        exit(-1);
    }
    if (pthread_create(&read_thread2,nullptr,read_fn,nullptr)!=0) {
        std::cout << "failure to create read pthread"  << std::endl;
        exit(-1);
    }
    if (pthread_create(&write_thread,nullptr,write_fn,nullptr)!=0) {
        std::cout << "failure to create write pthread" << std::endl;
        exit(-1);
    }
    sleep(10);
}

int main(int argc, char *argv[])
{
    create_thread();
    return 0;
}
