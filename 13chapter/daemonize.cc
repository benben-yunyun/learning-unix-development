#include <iostream>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <signal.h>
#include <sys/stat.h>           // for umask
#include <unistd.h>


void daemonize(const char * cmd)
{
    int i, fd0,fd1,fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    signal(SIGUSR1,SIG_IGN);
    std::cout << "run" << std::endl;
    // clear file creation mask
    // mode_t umask(mode_t cmask);
    // set the process's file mode creation mask to cmask and returns the previous value of the mask
    // 
    umask(0);
    std::cout << "run" << std::endl;
    // get maximum number of the file descriptors.
    if (getrlimit(RLIMIT_NOFILE,&rl)!=0) {
        std::cout << "getrlimit error" << std::endl;
        exit(-1);
    }
    std::cout << "run" << std::endl;

    // become a session leader to lose controlling TTY.
    if ((pid = fork()) < 0) {
        std::cout << "fork error" << std::endl;
        exit(-1);
    }
    else if (pid != 0) {
        std::cout << "fork parent return" << std::endl;
        exit(0);
    } 
    setsid();
    // pause to see 
    pause();
    // ensure future opens won't allocate controlling TTYs.
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGHUP,&sa,NULL) < 0) {
        exit(-1);
    }
    if ((pid=fork())<0) {
        exit(-1);
    }
    else if (pid != 0) {
        exit(0);
    }
    // change the current working directory to the root
    if (chdir("/")<0) {
        exit(-1);
    }
    // close all open file 
    if (rl.rlim_max == RLIM_INFINITY) {
        rl.rlim_max = 1024;
    }
    for ( i = 0; i < rl.rlim_max; ++i) {
        close(i);
    }

    // attach file descript 0,1,2 to /dev/null
    fd0 = open("/dev/null",O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    // init log
    openlog(cmd,LOG_CONS,LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR,"unexcepted file descriptors %d %d %d",fd0,fd1,fd2);
        exit(1);
    }
    syslog(LOG_INFO,"daemon_run_qixiang");
}

int main(int argc, char *argv[])
{
    daemonize("daemon");
    return 0;
}
