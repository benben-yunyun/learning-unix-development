#include <iostream>
#include <signal.h>

static void sig_usr(int);

int main(int argc, char *argv[])
{
  if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
    std::cout << "cannot catch SIGUSR1" << std::endl;
    exit(-1);
  }

  if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
    std::cout << "cannot catch SIGUSR2" << std::endl;
    exit(-1);
  }
  
  while(true) {}

  return 0;
}

static void sig_usr(int signo) {
  if (signo == SIGUSR1) {
    std::cout << "catch SIGUSR1" << std::endl;
  } else if (signo == SIGUSR2){
    std::cout << "catch SIGUSR2" << std::endl;
  } else {
    std::cout << "catch signal:[" << signo << "]\n";
  }
}
