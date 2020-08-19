// gcc -O0 -fno-stack-protector -no-pie stack1.c -o stack1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void shell(){
	printf("You did it.\n");
	system("/bin/sh");
}

int main(int argc, char** argv){
	int set_me = 0;
	char buf[15];
	puts("input the password:");
	read(0, buf, 0x20);
	if(set_me == 0xdeadbeef)
        shell();
	else
		printf("Not authenticated.\nset_me was %d\n", set_me);

	return EXIT_SUCCESS;
}
