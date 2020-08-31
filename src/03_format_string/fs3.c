// gcc -O0 fs3.c  -no-pie -o fs3
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){

    int set_me = 0x12345687;
    int *ptr = &set_me;
    // format string vuln
    puts("input your name plz");
    printf("hello, ");
    char buf[0x11];
    int n = read(0, buf, 0x10);
    buf[n] = 0;
    printf(buf);

    if (set_me == 0x12345678){
        printf("you did it\n");
        system("/bin/sh");
    }
    return 0;
}