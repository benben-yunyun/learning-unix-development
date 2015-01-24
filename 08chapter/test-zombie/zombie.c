#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void run() {

  pid_t pid = fork();
  
  if (pid<0) {
    printf("[ERROR] fork error\n");
    exit(-1);
  }
  
  if (pid==0) {
    printf("[INFO] child process exit\n");
    exit(0);
  }
  else {
    pid_t child;
    printf("[INFO] parent sleep\n");
    sleep(10);
    wait(&child);
    printf("[INFO] wait for %d\n",child);
    sleep(10);
    exit(0);
  }
}

int main(int argc, char *argv[])
{
  run();
  return 0;
}
