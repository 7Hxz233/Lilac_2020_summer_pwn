// gcc  -pie -fPIE fs4.c -o fs4
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
    int a = 0;
    int *b = &a;
    int **c = &b;

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

int main(){
    return vuln();
}