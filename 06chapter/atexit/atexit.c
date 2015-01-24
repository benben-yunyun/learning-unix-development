#include <stdio.h>
#include <stdlib.h>


void exit_handler(void) {
  puts("exit_handler");
}
void exit_handler2(void) {
  puts("exit_handler2");
}

int main(int argc, char *argv[])
{
  atexit(exit_handler);
  atexit(exit_handler2);
  return 0;
}
