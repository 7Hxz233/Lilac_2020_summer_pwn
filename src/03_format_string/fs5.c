// gcc  -pie -fPIE fs5.c -o fs5
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void shell(){
    system("/bin/sh");
}

int vuln(){
    char buf[0x30];
    while(1){
        puts("input sth");
        int n = read(0, buf, 0x1f);
        if (strncmp(buf, "quit", 4) == 0)
            break;
        buf[n] = 0;
        printf(buf);
    }
    puts("bye bye");
    return 0;
}

int func1(){
    vuln();
}

int main(){
    return func1();
    // printf("%p%n", 1, 2, 3);
    // printf(buf, )
}