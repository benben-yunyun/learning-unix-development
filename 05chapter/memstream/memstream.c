#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int convert_char_2_int(const char * ptr) {
  size_t len;
  char * buf;
  
  FILE * fp = open_memstream(&buf,&len);
  assert(fp!=NULL);

  fprintf(fp,"%s",ptr);
  fclose(fp);
  
  int  ret;
  sscanf(buf,"%d",&ret);
  return ret;
}


int main() {
  printf("%d",convert_char_2_int("10"));
  return 0;
}
