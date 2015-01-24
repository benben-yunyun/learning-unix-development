#include <stdio.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
#if defined(_POSIX_THREADS)
  printf("[INFO] define _POSIX_THREADS\n");
#endif
  
#if defined(_POSIX_ARG_MAX)
  printf("[INFO] define _POSIX_ARG_MAX:%d",_POSIX_ARG_MAX);
#endif
  printf("[INFO] define FIELNAME_MAX:%d\n",FILENAME_MAX);
  return 0;
}

