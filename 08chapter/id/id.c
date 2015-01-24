#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

void run() {
  printf("process id:%d\n",getpid());
  printf("parent process id:%d\n",getppid());
  printf("user id:%d\n",getuid());
  printf("effective user id:%d\n",geteuid());
  
  printf("=================================================\n=");
  struct passwd * pw = getpwuid(getuid());
  printf("pw name:%s\n",pw->pw_name);
  printf("pw passwd:%s\n",pw->pw_passwd);
  printf("==================================================\n");

  printf("group id:%d\n",getgid());
  printf("effective group id:%d\n",getegid());
  printf("==================================================\n");
  struct group * gp = getgrgid(getgid());
  printf("group name:%s\n",gp->gr_name);
  printf("group passwd:%s\n",gp->gr_passwd);
  for (int i = 0; gp->gr_mem[i]!=NULL;++i) {
    printf("member:%s\n",gp->gr_mem[i]);
  }
}

int main(int argc, char *argv[])
{
  run();
  return 0;
}
