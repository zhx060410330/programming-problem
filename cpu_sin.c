#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
 
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
    int i, j, tmp;
    for (;;){
        /// 20s per cycle,
        for (j = 0; j < 20000; ++j){
            tmp = 70000 + 70000 * sin(2 * 3.14 / 20000 * j);
            for (i = 0; i < tmp; ++i);
            nanosleep(&idle, &returnTime);
        }
    }
    return 0;
}
