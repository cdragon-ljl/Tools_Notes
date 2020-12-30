# GDB使用

GDB全称”GNU symbolic debugger"，是Linux下常用的程序调试器。实际场景中，GDB常用来调试C和C++程序。

总的来说，借助GDB调试器可以实现以下几个功能：

* 程序启动时，可以按照我们自定义的要求运行程序，例如设置参数和环境变量；
* 可使被调试程序在指定代码处暂停运行，并查看当前程序的运行状态（例如当前变量的值，函数的执行结果等），即支持断点调试；
* 程序执行过程中，可以改变某个变量的值，还可以改变代码的执行顺序，从而尝试修改程序中出现的逻辑错误

## 安装GDB

### Ubuntu安装gdb

```shell
sudo apt-get install gdb
```

### Centos安装gdb

```shell
sudo yum -y install gdb
```

## 编译待调试的程序

```shell
g++ *.cpp -g -o *
```

## 启动gdb

```shell
gdb *
```

![image-20201219095144438](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20201219095144438.png)

**启动可用参数**

| parameter         | short     | function                                 |
| ----------------- | --------- | ---------------------------------------- |
| -pid number       | -p number | 调试进程ID为number的程序                 |
| -symbols file     | -s file   | 仅从指定file文件中读取符号表             |
| -q -quiet -silent |           | 取消启动gdb时打印的介绍信息和版权信息    |
| -cd dir           |           | 以dir作为启动gdb的工作目录，而非当前目录 |
| --args p1 p2      |           | 向可执行文件传递执行所需的参数           |



## 调试命令

| command           | short | function                                                     |
| ----------------- | ----- | ------------------------------------------------------------ |
| (gdb) break xxx   | b xxx | 在源代码指定的某一行设置断点                                 |
| (gdb) run         | r     | 执行被调试的程序，会自动在第一个断点处暂停执行               |
| (gdb) continue    | c     | 当程序在某一断点处停止运行后，使用该命令可以继续执行，直至遇到下一个断点或程序结束 |
| (gdb) next        | n     | 令程序一行一行的执行                                         |
| (gdb) print xxx   | p xxx | 打印指定变量的值                                             |
| (gdb) list        | l     | 显示源代码的内容，包括各行代码所在的行号（每次10行）         |
| (gdb) quit        | q     | 退出调试                                                     |
| (gdb) step        | s     | 执行下一行语句，如果有函数调用则进入函数                     |
| (gdb) set var x=x |       | 修改变量的值                                                 |
| (gdb) start       |       | 开始执行程序，停在main函数第一行语句前面等待命令             |



