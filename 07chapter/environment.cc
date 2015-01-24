#include <iostream>
#include <cstdlib>

extern char ** environ;
int main(int argc, char *argv[])
{
  int index =  0;
  while (environ[index]!=NULL) {
    std::cout << environ[index] << std::endl;
    ++ index;
  }
  return 0;
}
