
// gcc ./sc1.c -g -o sc1
int main(){
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
