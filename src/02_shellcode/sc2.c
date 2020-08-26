// gcc  -fno-stack-protector -z execstack -no-pie sc2.c -o sc2
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char bss_buf[0x100];

int main(int argc, char** argv){
	char buf[0x70];
    write(1, "input ur name plz\n", 18);
	int n = read(0, buf, 0x100);
    memcpy(bss_buf, buf, 0x100);
    write(1, "bye bye", 7);
    write(1, bss_buf, n);
	return 0;
}
