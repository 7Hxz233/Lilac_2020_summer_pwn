// gcc  -fno-stack-protector -z execstack -no-pie sc3.c -o sc3 -lseccomp
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
	rc = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
	if (rc < 0)
		goto out;
	rc = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
	if (rc < 0)
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
