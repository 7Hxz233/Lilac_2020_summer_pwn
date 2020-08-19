// gcc -O0 -fno-stack-protector stack3.c  -no-pie -o stack3
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *sh_str = "/bin/sh";

void shell(char* cmd){
	system(cmd);
}

void print_name(char* input) {
	char buf[15];
	// strcpy(buf, input);
	memcpy(buf, input, 0x100);
	printf("Hello %s\n", buf);
}

int test_parament(
	int a1,
	int a2;
	int a3;
	int a4;
	int a5;
	int a6;
	int a7;
){
	return 0x1234;
}

int main(int argc, char** argv){

	test_parament(1, 2, 3, 4, 5, 6, 7);
	char buf[0x100];
    puts("welcome to stack3");
	puts("input your name plz");
	read(0, buf, 0x100);

	print_name(buf);

	return EXIT_SUCCESS;
}
