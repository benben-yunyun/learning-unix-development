#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
  char buf[1024];
  FILE * fp = fopen("test","w+");
  assert(fp!=NULL);
  setbuf(fp,buf);
  fprintf(fp,"testlalalalal\n");
  printf("%s",buf);

  fseek(fp,0,SEEK_SET);
  
  fprintf(fp,"begin\n");
  
  fclose(fp);

  printf("[INFO] test fgets:\n");
  fgets(buf,1024,stdin);
  printf("[INFO] buf:%s",buf);
  return 0;
}
