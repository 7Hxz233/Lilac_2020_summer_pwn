// gcc -O0 -g -no-pie heap2.c -o heap2
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <alloca.h>

void die(char *msg){
    puts(msg);
    exit(-1);
}

void *ptrs[0x10];



int get_int(){
    // puts("")
    char buf[0x10] = {0};
    read(0, buf, 0x0f);
    return atoi(buf);
}

int menu(){
    puts("1. add");
    puts("2. rm");
    puts("3. show");
    puts("4. edit");
    puts("5. exit");
    printf("input your choice : ");
    return get_int();
}


int main(){
    setbuf(stdin, 0);
    setbuf(stdout, 0);
    setbuf(stderr, 0);
    // test_chunk();
    int choice;
    while ((choice = menu()) != 5) {
        if (choice == 1) {
            printf("input idx plz : ");
            unsigned int idx = get_int();
            if (0x10 <= idx ) die("wrong idx");
            printf("input size plz : ");
            unsigned int size = get_int();
            void *ptr = malloc(size);
            if (ptr == NULL) die("malloc error");
            ptrs[idx] = ptr;
        } else if (choice == 2) {
            printf("input idx plz : ");
            unsigned int idx = get_int();
            if (0x10 <= idx ) die("wrong idx");
            free(ptrs[idx]); // uaf
        } else if (choice == 3){
            printf("input idx plz : ");
            unsigned int idx = get_int();
            if (0x10 <= idx ) die("wrong idx");
            puts(ptrs[idx]);
        } else if (choice == 4){
            puts("un implemented yet");
        } else {
            puts("wrong choice");
        }
    }
    return 0;
}