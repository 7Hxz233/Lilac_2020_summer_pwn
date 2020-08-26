// gcc  -fno-stack-protector -z execstack -no-pie sc2.c -o sc2
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


char bss_buf[0x400];

int main(int argc, char** argv){
	char buf[0x400];
    write(1, "input ur name plz\n", 18);
	int n = read(0, buf, 0x500);
    for(int i = 0; i < 0x400; i++){
        char ch = buf[i];
        if (ch >= 0x80) break;
        bss_buf[i] = buf[i];
    }
    write(1, "bye bye", 7);
    void (* p)(void) = &bss_buf;
    p();
    
	return 0;
}
