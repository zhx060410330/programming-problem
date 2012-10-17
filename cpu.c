#include <stdio.h>
#include <time.h>
#include <unistd.h>
 
int main(int argc, char *argv[])
{
    unsigned long mask = 1;
    unsigned int len = sizeof(mask);
 
    if (sched_setaffinity(0, len, &mask) < 0) {
        perror("sched_setaffinity");
        return -1;
    }
 
    struct timespec idle = {0, 500000};
    struct timespec returnTime;
    int i;
    for (;;){
        for (i = 0; i < 70000; ++i);
 
        nanosleep(&idle, &returnTime);
    }
    return 0;
}
