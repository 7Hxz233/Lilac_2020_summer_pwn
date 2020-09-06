// gcc -g -O0 -fno-stack-protector dl2.c  -no-pie -o dl2
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void print_name(char* input) {
	char buf[0x20];
	// strcpy(buf, input);
	memcpy(buf, input, 0x100);
	printf("Hello %s\n", buf);
}

int main(int argc, char** argv) {
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	char buf[0x100];
    puts("welcome to dl2");
	// printf("Here is a gift: %p\n", stdout);
	puts("input your name plz");

	read(0, buf, 0x100);

	print_name(buf);

	return EXIT_SUCCESS;
}
