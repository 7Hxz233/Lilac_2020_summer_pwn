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

// sudo apt install libseccomp-dev
// gcc ./sc1_seccomp.c -g -o sc1_seccomp -lseccomp
int main(){
    if (init_seccomp() != 0)
        die("init_seccomp failed");
    char *binsh = "/bin/sh\0";
    __asm__ ("mov $59, %%rax\n\t"
        "mov %0, %%rdi\n\t"
        "xor %%rsi, %%rsi\n\t"
        "xor %%rdx, %%rdx\n\t"
        "syscall\n\t"
        :
        : "r"(binsh)
        : "rax"
    );
    return 0;
}
