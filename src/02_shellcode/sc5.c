// gcc  -fno-stack-protector -z execstack -no-pie sc5.c -o sc5 -lseccomp
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <seccomp.h>
#include <linux/seccomp.h>


void die(char *msg){
    puts(msg);
    exit(-1);
}

int init_seccomp() {
	scmp_filter_ctx ctx;
	int rc = -1;
	ctx = seccomp_init(SCMP_ACT_KILL);
	if (ctx == NULL)
		goto out;
	rc = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);
	if (rc < 0)
		goto out;
	rc = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
	if (rc < 0)
		goto out;
	rc = seccomp_load(ctx);
	if (rc < 0)
		goto out;
	return 0;
out:
	seccomp_release(ctx);
	return -1;
}



char bss_buf[0x20];
char flag[0x20];

int main(int argc, char** argv){
	char buf[0x400];
	int fd;
	if ((fd = open("./flag", O_RDONLY)) < 0) die("open flag error");
	if (read(fd, flag, 0x40) <= 0) die("read flag error");
	write(1, "input your shellcode\n", 21);
	int n = read(0, bss_buf, 0x20);

	init_seccomp();

    void (* p)(void) = &bss_buf;
    p();
    
	return 0;
}
