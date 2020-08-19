// gcc -O0 -fno-stack-protector stack4.c  -no-pie -o stack4
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *sh_str = "/bin/sh";

void shell(char* cmd){
	system(cmd);
}

void print_name(char* input) {
	char buf[0x20];
	// strcpy(buf, input);
	memcpy(buf, input, 0x22);
	printf("Hello %s\n", buf);
}

int main(int argc, char** argv){
	char buf[0x100];
    puts("welcome to stack4");
	printf("here is a gift: %p\n", buf);
	puts("input your name plz");
	read(0, buf, 0x100);

	print_name(buf);

	return EXIT_SUCCESS;
}
