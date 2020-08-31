// gcc -O0 fs1.c  -no-pie -o fs1
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char buf[0x10];

    // 传参方法
    printf("%d, %d, %d, %d, %d, %d, %d, %d\n", 1, 2, 3, 4, 5, 6, 7, 8);

    // 一些常见的 Flag characters
    printf( "a decimal number   : %d\n"
            "a char             : '%c'\n"
            "16 chars           : \"%16c\"\n"
            "a pointer number   : %p\n"
            "a hex number       : %x\n", 123, 'h', 'a', &buf, 0xdeadbeef);
    
    // 存储已经输出的字符数量
    // int *
    int a = 0x12345678;
    printf("a is %#x\n", a);
    printf("abc%n\n", &a);
    printf("a is %#x\n", a);

    // short *
    a = 0x12345678;
    printf("a is %#x\n", a);
    printf("abc%hn\n", &a);
    printf("a is %#x\n", a);

    // char *
    a = 0x12345678;
    printf("a is %#x\n", a);
    printf("%16c%hhn\n", &a);
    printf("a is %#x\n", a);

    // 申明使用第几个参数
    printf("second number is %2$d\n", 111, 222);

    // 设置宽度
    printf("\n%5$*4$c\n", 1, 2, 3, 233, 'c');

    // format string vuln
    int n = read(0, buf, 0x1f);
    buf[n] = 0;

    printf(buf);
}