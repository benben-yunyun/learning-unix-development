#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IRGRP|S_IROTH|S_IWOTH)

int main(void) {
  umask(00);
  if (creat("foo",RWRWRW) < 0) {
    printf("create error for foo :[%s]\n",strerror(errno));
    return 0;
  }
  umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  if (creat("bar",RWRWRW) < 0) {
    printf("create error for bar :[%s]\n",strerror(errno));
    return 0;
  }
  return 0;
}
