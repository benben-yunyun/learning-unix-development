#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
  pid_t pid;
  
  if ((pid=fork())<0) {
    printf("fork error\n");
    return -1;
  } else if (pid==0) {
    if (execl("/Users/qixiang/Documents/workspace/learn/linux/unix-development/learning-apue/08chapter/interpret/testinterp","testinterp","myarg1","MY ARGS2",(char*)0)<0) {
      printf("execl error\n");
      perror("execl");
      return -1;
    }
  }
  if (waitpid(pid,NULL,0) < 0) {
    printf("waitpid error\n");
    return -1;
  }
  return 0;
}
