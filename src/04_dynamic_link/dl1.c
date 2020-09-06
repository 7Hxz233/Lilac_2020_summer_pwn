// gcc -O0 -no-pie dl1.c -o dl1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>



int main(){
    printf("hello %s\n", "ikun");
    puts("bye bye");    
    // printf("hello world\n");
    return 0;
}