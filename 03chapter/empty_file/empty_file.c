#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main(int argc, char *argv[])
{
  int fd;
  if ((fd=creat("file.hole",S_IRUSR|S_IXUSR|S_IROTH)) < 0) {
    perror("cannot create file.hole:");
    return -1;
  } 
  
  if (write(fd,buf1,10)!=10) {
    perror("cannot write buf1:");
    close(fd);
    return -1;
  }

  if (lseek(fd,16384,SEEK_SET)==-1) {
    perror("cannot lseek:");
    close(fd);
    return -1;
  }
  
  if (write(fd,buf2,10)!=10) {
    perror("cannot write buf2:");
    close(fd);
    return -1;
  }
  close(fd);
  return 0;
}
