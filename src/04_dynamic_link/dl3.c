// gcc -g -O0 dl3.c  -no-pie -o dl3
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int get_int(){
	char buf[0x10] = {0};
	// buf[0x0f] = 0;
	read(0, buf, 0x0f);
	return atoi(buf);
}

long long get_ll(){
	char buf[0x20] = {0};
	// buf[0x0f] = 0;
	read(0, buf, 0x1f);
	return atoll(buf);
}

int get_choice(){
	char buf[0x10];
	buf[0x0f] = 0;
	puts("1. read 8 bytes");
	puts("2. write 8 bytes");
	printf("input the choice:");
	read(0, buf, 0x0f);
	return atoi(buf);
}

int main(int argc, char** argv) {
	// char buf[0x100];
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
    puts("welcome to dl3");
	int choice = 3;
	int cnt = 0;
	while ((choice = get_choice()) != 3 && (cnt++ < 5)){
		if (choice == 1) {
			printf("input addr : ");
			long long *addr = get_ll();
			write(1, addr, 8);
		} else if (choice == 2) {
			printf("input addr : ");
			long long *addr = get_ll();
			printf("input value : ");
			long long value = get_ll();
			*addr = value;
		} else {
			puts("invalid choice");
		}
	}
	puts("bye bye");
	return EXIT_SUCCESS;
}
