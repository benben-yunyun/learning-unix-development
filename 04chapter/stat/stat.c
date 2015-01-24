#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>


/**
 * @brief stat functions
 *  
 * int stat(const char *restrict pathname, struct stat * restrict buf);
 * int fstat(int fd, struct stat * buf);
 * int lstat(const char * restrict pathname, struct stat * restrict buf); for symbolic link
 * int fstatat(int fd, const char * restrict pathname,struct stat * restrict buf, int flag); flag control follow the symbolic
 *
 * @return: 0 if ok, -1 if error
 *
 */


/**
 * @brief stat: return a stat of pathname.
 *
 * int stat(const char * restrict pathname, struct stat * restrict buf);
 *
 * @param pathname path name
 * @param 
 *
 */
void test_stat() {
  struct stat buf;
  char * ptr;
  if (lstat("./stat.c",&buf)<0) {
    printf("[ERROR] lstat error");
  }
  if (S_ISREG(buf.st_mode)) {
    ptr = "regular";
  } else if (S_ISDIR(buf.st_mode)) {
    ptr = "directory";
  }
  printf("%s",ptr);
}

int main(int argc, char *argv[])
{
  test_stat();
  return 0;
}
