// gcc -O0 -g -no-pie heap1.c -o heap1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <alloca.h>

int arr_bss[0x100];

void basic(){
    // // int *arr_stack = alloca(0x1000);
    // int *arr_stack = alloca(0x1000000);
    // arr_stack[0] = 1;

    int *arr_heap = malloc(0x20);
    arr_heap[0] = 123;
    free(arr_heap);
}

int test_chunk(){
    void *A = malloc(0x20);
    void *B = malloc(0x30);
    void *C = malloc(0x40);
    printf("A: %p\nB: %p\nC: %p\n", A, B, C);
}

int test_free_chunk(){
    void *fast1 = malloc(0x20);
    void *fast2 = malloc(0x20);
    void *fast3 = malloc(0x30);
    // printf("fast1: %p\nfast2: %p\nfast3: %p\n", fast1, fast2, fast3);
    free(fast1);
    free(fast2);
    free(fast3);

    void *unsorted1 = malloc(0x80);
    // printf("unsorted1: %p\n", unsorted1);
    malloc(0x20);
    free(unsorted1);
}

int main(){
    test_free_chunk();
    return 0;
}