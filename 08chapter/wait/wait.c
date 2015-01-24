#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/* 检测process结果的macro 
 *
 * WIFEXITED(status) 判断返回是否是正常退出；
 * 可以调用WEXITSTATUS(status)得到低8bits，该低8bits是子进程传给exit,_exit,_Exit的参数。
 *
 * WIFSIGNALED(status) 判断返回是否由于子进程因为接受不可处理信号的原因，引起异常。
 * 可以调用WTERMSIG(status) 抽取引起异常的信号。
 * 可以调用WCOREDUMP(status) 判断异常是否产生了core文件
 *
 * WIFSTOPPED(status) 判断子进程是否stoppped。
 * WSTOPSIG(status) 得到引起stop的信号。
 *
 * WIFCONTINUED(status) 判断子进程是否继续
 *
 */

void pr_exit(int status) {
  if (WIFEXITED(status)) 
    printf("normal termination,exit status = %d\n",
           WEXITSTATUS(status));
  else if (WIFSIGNALED(status)) 
    printf("abnormal termination, signal number = %d%s\n",
           WTERMSIG(status),
#ifdef WCOREDUMP
           WCOREDUMP(status) ? " (core file generated)" : "");
#else
  "");
#endif
 else if (WIFSTOPPED(status)) 
   printf("child stopped, signal number = %d\n",
          WSTOPSIG(status));
}

int main(int argc, char *argv[])
{
  pid_t pid;
  int status;
  if ((pid = fork()) <0) {
    printf("[ERROR] fork error\n");
    exit(-1);
  } else if (pid == 0)          /* for child */
    exit(7);
  
  if (wait(&status) != pid) {   /* wait for child */
    printf("[ERROR] wait error");
    exit(-1);
  }

  pr_exit(status);

  if ((pid = fork()) < 0) {
    printf("[ERROR] fork error\n");
    exit(-1);
  } else if (pid == 0 ){        /* child */
    abort();
  }
    
  if (wait(&status)!=pid) {     /* wait for child */
    printf("[ERROR] wait error\n");
    exit(-1);
  } 
  
  pr_exit(status);

  if ((pid = fork()) < 0) {
    printf("[ERROR] fork error\n");
    exit(-1);
  } else if (pid==0) {
    status /= 0;                /* generate sigfpe */
  }
    
  if (wait(&status) != pid) {   /* wait for child */
    printf("[ERROR] wait error\n");
    exit(-1);
  }
  pr_exit(status);
  return 0;
}
