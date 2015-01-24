#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void run() {
  pid_t pid = fork();

  if (pid==-1) {
    printf("[ERROR] fork error\n");
    exit(0);
  }

  if (pid==0) {                 /* child process */
    printf("[INFO] get parent pid:%d\n",getppid());
  } else {                      /* parent process */
    printf("[INFO] child id:%d\nprocess id:%d\n",pid,getpid());
  }

}

int main(int argc, char *argv[])
{
  run();
  return 0;
}
