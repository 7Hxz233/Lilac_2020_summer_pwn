<!-- TOC -->

- [1. Lilac_2020_summer_pwn](#1-lilac_2020_summer_pwn)
- [2. 源码对应知识点](#2-源码对应知识点)
  - [2.1. stack 文件夹:](#21-stack-文件夹)
  - [2.2. shellcode 文件夹:](#22-shellcode-文件夹)
  - [2.3. format_string 文件夹:](#23-format_string-文件夹)
  - [2.4. 动态链接(plt表和got表)](#24-动态链接plt表和got表)
  - [2.5. 常见漏洞类型](#25-常见漏洞类型)
  - [2.6. 堆入门](#26-堆入门)
  - [2.7. iofile](#27-iofile)
  - [2.8. 堆进阶](#28-堆进阶)
- [3. 环境配置](#3-环境配置)
  - [3.1. 基本环境](#31-基本环境)
  - [3.2. 学习资源](#32-学习资源)

<!-- /TOC -->

# 1. Lilac_2020_summer_pwn

Lilac 2020 暑期pwn培训课件以及相关文件

开始上课之前需要安装一些软件并配置一些环境. 具体软件及配置方法参考[3. 环境配置](#3-环境配置)

培训录屏会上传到[B站频道](https://space.bilibili.com/40145638/channel/detail?cid=145242)

本仓库中:
- `slides` 文件夹中为课件(*.pptx).
- `src` 文件夹中为讲课过程中用到的练习题源码及对应exp.


# 2. 源码对应知识点

## 2.1. stack 文件夹:

栈溢出相关练习题

1. stack1.c: 覆盖局部变量
2. stack2.c: 覆盖返回地址到后门函数
3. stack3.c: 覆盖返回地址到后门函数, 并利用rop控制参数.
4. stack4.c: 提供后门函数栈地址, 但是只能覆盖到 rbp. 需要进行栈迁移+rop
5. stack5.c: 没有后门函数, 提供了libc中某个函数地址, 需要计算system地址, 并覆盖返回地址到system


## 2.2. shellcode 文件夹:

shellcode 相关练习题

1. sc1.c:  使用syscall get shell
1. sc1_seccomp.c:  加了seccomp规则之后无法使用syscall get shell
2. sc2.c: ret2shellcode
3. sc3.c: orwshellcode
4. sc4.c: printable shellcode
5. sc5.c: 侧信道 leak flag


## 2.3. format_string 文件夹:

格式化字符串(format string) 相关练习题

1. fs1.c: printf的一些基本用法
2. fs2.c: 利用格式化字符串漏洞泄露栈上的变量
3. fs3.c: 利用格式化字符漏洞修改栈上的变量
4. fs4.c: 利用格式化字符漏洞修改返回地址指向后门函数

## 2.4. 动态链接(plt表和got表)

1. dl1.c: 调用两个libc函数, 用以展示动态链接的过程
2. dl2.c: 栈溢出, 泄露got表中的libc地址, 然后ret2libc
3. dl3.c: 修改 got表中atoi项为system地址. 然后getshell

## 2.5. 常见漏洞类型

todo

## 2.6. 堆入门

todo

## 2.7. iofile

todo

## 2.8. 堆进阶

todo

# 3. 环境配置

## 3.1. 基本环境

pwn题通常都是linux系统下的可执行文件, 所以学pwn的话需要有一个linux系统, 如果你的操作系统是windows或者 OSX 的话建议先安装一个虚拟机软件, 然后在虚拟机里面装一个linux系统. 推荐使用ubuntu系统, 本次培训过程中默认大家的环境都是 ubuntu 16.04. 所以如果你用的linux不是 ubuntu 的话建议也装一个虚拟机或者使用 docker.

同时分析可执行文件的过程中需要用到一些软件. 比如使用 IDA 进行静态分析. 使用 gdb 进行动态调试. 下面列出一些可能会用到的软件

1. IDA: 自行搜索
2. 虚拟机软件: 
    1. vmware: 该软件正版需要花钱买, 想用这个的自行搜索吧.
    2. virtual box: 开源免费. https://www.virtualbox.org/wiki/Downloads
3. ubuntu系统镜像下载地址:
   1. https://mirrors.tuna.tsinghua.edu.cn/ubuntu-releases/16.04.6/ubuntu-16.04.6-desktop-amd64.iso

*本次培训过程中讲师使用的环境为virtualbox下ubuntu 16.04*

*在虚拟机中安装ubuntu的方法自行搜索,不再赘述.安装好系统之后最好配置一下共享文件夹, 这样的话windows和linux之间传输文件就比较方便*

## 3.2. 学习资源

pwn题拿到的通常是一个linux下的可执行文件, 其中包含了一些漏洞, 选手需要经过一些逆向操作来弄懂程序的运行逻辑, 进而发现并利用漏洞. 如果写过c语言了解程序编译成可执行文件的过程的话就应该知道可执行文件主要是由机器码组成的, 和机器码一一对应的是汇编代码, 大概长这样.

```asm
.LC0:
        .string "hello world!"
mian:
        push    rbp
        mov     rbp, rsp
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        mov     eax, 0
        pop     rbp
        ret
```

这儿有一个网站可以查看各种高级语言(c/c++等)编译得到的汇编语言, 上面的汇编语言就是下面这段c语言代码编译得到的.

```c
// Type your code here, or load an example.
int mian(){
    puts("hello world!");
    return 0;
}
```
网站地址: [https://godbolt.org/](https://godbolt.org/)

所以我们要想弄懂程序的运行逻辑的话就需要具有基本的汇编代码的阅读能力. 关于汇编语言的学习可以参考 王爽的 <<汇编语言>> 一书. (不用全看完, 可以看懂常见汇编指令即可)


在利用漏洞的过程中, 我们通常需要写一些自动化利用脚本, 通常使用python语言, 所以需要了解一下python的基本语法. 网上关于python的教程很多, 这儿提供一个[教程](https://www.runoob.com/python/python-tutorial.html)

在做题的过程中需要离不开linux系统, 所以希望大家在装好ubuntu之后可以熟悉一下linux系统的基本操作.(主要是shell下的一些命令), 可以参考一下这个教程: https://zhuanlan.zhihu.com/p/36801617

在动态分析题目的过程中我们往往需要使用gdb调试题目文件, 但是gdb如果不装插件的话极其难用, 所以强烈推荐大家装个插件, 常用的插件由三个. 

1. peda: https://github.com/longld/peda (安装简单/提供了一些基础功能, 本次培训堆之前的课程都使用该插件)
2. gef: https://github.com/hugsy/gef (没用过不评价)
3. pwndbg: http://pwnwndbg.com/ (安装比较麻烦, 但是功能强大, 对堆支持比较完善)

在写利用脚本的过程中会用到python的一个库 `pwntools`, 大家可以自行安装之后体验一番. 安装方式参考官网: https://github.com/Gallopsled/pwntools. 关于这个库的使用可以参考一下这篇教程: https://bbs.pediy.com/thread-247217.htm

总结一下:

1. 汇编语言
   1. 在线网站: https://godbolt.org/ 
   2. 书籍: <<汇编语言>> 王爽
2. python入门教程
   1. https://www.runoob.com/python/python-tutorial.html
3. linux基本操作
   1. https://zhuanlan.zhihu.com/p/36801617
4. gdb插件
   1. gef, peda, pwndbg
5. pwntools
   1. 入门教程: https://bbs.pediy.com/thread-247217.htm
   2. 官网: https://github.com/Gallopsled/pwntools
   3. 官方文档: http://docs.pwntools.com/en/stable/ 