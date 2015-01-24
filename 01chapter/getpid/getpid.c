#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  printf("[INFO] getpid:%d\n",getpid());
  printf("[INFO] getuid:%d\n",getuid());
  printf("[INFO] getgid:%d\n",getgid());
  return 0;
}
