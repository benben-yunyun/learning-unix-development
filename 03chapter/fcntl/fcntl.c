#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


/**
 * @brief int fcntl(int fd, int cmd, ... int args);
 * 
 * change the properties of a file that already open.
 * 
 * @param[in]  fd file handler that will be change
 * @param[in] cmd command of how to change property of the file
 *            - F_DUPFD or F_DUPFD_CLOEXEC Duplicate an existing descriptor
 *            - F_GETFD or F_SETFD Get or Set file descriptor flags
 *            - F_GETFL or F_SETFL Get or Set file status flags
 *            - F_GETOWN or F_SETOWN Get or Set asynchronous I/O ownership
 *            - F_GETLK,F_SETLK or F_SETLKW Get or Set record locks
 * @param[in] args options on cmd
 */
void test_fcntl(char * filename) {
  int val;
  if ((val = fcntl(atoi(filename),F_GETFL,0))<0) {
    printf("error fcntl\n");
  }
  switch(val & O_ACCMODE) {
  case O_RDONLY:
    printf("read only");
    break;
  case O_WRONLY:
    printf("write only");
    break;
  case O_RDWR:
    printf("read and write");
    break;
  }
  if (val & O_APPEND) {
    printf(", append");
  }
  if (val & O_NONBLOCK) {
    printf(", NONBLOCK");
  }
  
}
int main(int argc, char *argv[])
{
  
  return 0;
}
