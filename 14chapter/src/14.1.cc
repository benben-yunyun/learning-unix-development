#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
char buf[500000];
int main(int argc, char *argv[])
{
    int ntowrite, nwrite;
    char * ptr;

    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);
    set_fl(STDOUT_FIFLENO, O_NONBLOCK);

    
    return 0;
}
