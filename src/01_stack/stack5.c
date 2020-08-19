// gcc -O0 -fno-stack-protector stack5.c  -no-pie -o stack5
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
	char buf[0x100];
    puts("welcome to stack5");
	printf("Here is a gift: %p\n", stdout);
	puts("input your name plz");

	read(0, buf, 0x100);

	print_name(buf);

	return EXIT_SUCCESS;
}
