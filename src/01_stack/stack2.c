// gcc -O0 -g -fno-stack-protector -no-pie stack2.c -o stack2
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void shell(){
	system("/bin/sh");
}

void print_name(char* input) {
	char buf[15];
	// strcpy(buf, input);
	memcpy(buf, input, 0x100);
	printf("Hello %s\n", buf);
}

int main(int argc, char** argv)
{
	char buf[0x100];
    puts("welcome to stack2");
	puts("input your name plz");
	read(0, buf, 0x100);

	print_name(buf);

	return EXIT_SUCCESS;
}
