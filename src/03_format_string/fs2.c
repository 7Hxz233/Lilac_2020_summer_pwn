// gcc -O0 fs2.c  -no-pie -o fs2
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
    srand(time(NULL));
    int random = rand();

    // format string vuln
    puts("input your name plz");
    printf("hello, ");
    char buf[6];
    int n = read(0, buf, 5);
    buf[n] = 0;
    printf(buf);

    printf("try guess the number: ");
    int input = 0;
    scanf("%d", &input);

    if (input == random){
        printf("you did it\n");
        system("/bin/sh");
    }
}