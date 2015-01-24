#include "apue.h"

int main(int argc, char *argv[])
{
  err_msg("test err_msg:%s","ok");
  info_msg("test info_msg:%s","ok");
  err_dump("test err_dump:%s","ok");
  return 0;
}
