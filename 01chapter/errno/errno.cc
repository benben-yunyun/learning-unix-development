#include <stdio.h>              // for perror
#include <stdlib.h>
#include <errno.h>              //定义error相关定义
#include <string.h>             // for strerror;

// perror: 根据errno输出一条字符串到标准输出
// strerror: 根据error返回一个字符串

int main(int argc, char *argv[])
{
  fprintf(stderr,"EACCES: %s\n",strerror(EACCES));
  errno = ENOENT;
  perror(argv[0]);
  return 0;
}
