#include <unistd.h>
#include <iostream>


int main() {
  std::cout << "pid:" << getpid() << std::endl;
  std::cout << "group id:" << getpgrp() << std::endl;
  std::cout << "session id:" << getsid(0) << std::endl;
  exit(0);
}
