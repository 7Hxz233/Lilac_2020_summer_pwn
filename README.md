# Lilac_2020_summer_pwn
Lilac 2020 暑期pwn培训课件以及相关文件

培训录屏会上传到[B站](https://space.bilibili.com/40145638)

`slides` 文件夹中为课件

`src` 文件夹中为讲课过程中用到的源码.


# 源码对应知识点

## 01_stack 文件夹:

栈溢出相关练习题

1. stack1.c: 覆盖局部变量
2. stack2.c: 覆盖返回地址到后门函数
3. stack3.c: 覆盖返回地址到后门函数, 并利用rop控制参数.
4. stack4.c: 提供后门函数栈地址, 但是只能覆盖到 rbp. 需要进行栈迁移+rop
5. stack5.c: 没有后门函数, 提供了libc中某个函数地址, 需要计算system地址, 并覆盖返回地址到system


## 02_shellcode 文件夹:

1. sc1.c:  使用syscall get shell
1. sc1_seccomp.c:  加了seccomp规则之后无法使用syscall get shell
2. sc2.c: ret2shellcode
3. sc3.c: orwshellcode
4. sc4.c: printable shellcode
5. sc5.c: 侧信道 leak flag