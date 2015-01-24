#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 4096

int main(int argc, char *argv[])
{
  char buf[MAXLINE];
  pid_t pid;
  int status;
  
  printf("%% ");
  while (fgets(buf,MAXLINE,stdin)!=NULL) {
    if (buf[strlen(buf)-1]=='\n')
      buf[strlen(buf)-1] = '\0';

    if ((pid=fork())<0) {
      printf("fork error");
      abort();
    } else if (pid==0) {
      execlp(buf,buf,(char*)0); // 在系统变量PATH中查找可执行的命令，并将第二参数以后的变量当成执行的参数
      printf("cannot execute: %s",buf);
      abort();
    } 
    
    if ((pid=waitpid(pid,&status,0))<0) {
      printf("waitpid error");
      abort();
    }
    printf("%% ");
  }
  return 0;
}
