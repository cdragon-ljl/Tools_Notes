# Makefile

参考学习于：[跟我一起写Makefile](https://blog.csdn.net/haoel/article/details/2886)

## 关于程序编译

一般来说，无论是**C、C++**都要首先把源文件编译成中间代码文件，在**Windows**下也就是**.obj**文件，UNIX下是**.o**文件，即**Object File**，这个动作叫做编译**compile**。然后再把大量的**Object File**合成执行文件，这个动作叫做链接**Link**。编译时，编译器需要的是语法的正确，函数与变量的声明的正确。对于后者，通常需要告诉编译器头文件的所在位置（头文件中应该只是声明，而定义应该放在**C/C++**文件中），只要所有的语法正确，编译器就可以编译出中间目标文件。一般来说，每个源文件都应该对应于一个中间目标文件（**O**文件或是**OBJ**文件）。链接时，主要是链接函数和全局变量，所以我们可以使用这些中间目标文件（**O**文件或是**OBJ**文件）来链接我们的应用程序。链接器并不管函数所在的源文件，直观函数的中间目标文件**（Object File）**，在大多数时候，由于源文件太多，编译生成的中间目标文件太多，而在链接时需要明显地指出中间目标文件名，这对于编译很不方便，所以，我们要给中间目标文件打个包，在**Windows**下这种包叫“库文件”**（Library File）**，也就是**.lib**文件，在**UNIX**下，是**Archive File**，也就是**.a**文件。

源文件首先会生成中间目标文件，再由中间目标文件生成执行文件。在编译时，编译器只检测程序语法，和函数、变量是否被声明。如果函数未被声明，编译器会给出一个警告，但可以生成**Object File**。而在链接程序时，链接器会在所有的**Object File**中找寻函数的实现，如果找不到，那就会报链接错误码**Linker Error**。在 **VC** 下，这种错 误一般是：**Link 2001 **错误，意思说是说，链接器未能找到函数的实现。你需要指定函数的 **Object File**。    

## Makefile介绍

`make`命令执行时，需要一个`Makefile`文件，以告诉`make`命令需要怎么样的去编译和链接程序。写一个`Makefile`来告诉`make`命令如何编译和链接文件时，我们的规则是：

1. 如果这个工程没有编译过，那么我们的所有C文件都要被编译并被链接。
2. 如果这个工程的某几个C文件被修改，那么我们只编译被修改的C文件，并链接目标程序。
3. 如果这个工程的头文件被改变了，那么我们需要编译引用了这几个头文件的C文件，并链接目标程序。

### Makefile的规则

```makefile
target ...:prerequisites ...
command
...
...
```

`target`也就是一个目标文件，可以是`Object File`，也可以是执行文件，还可以是一个标签。`prerequisites`就是，要生成那个`target`所需要的的文件或者是目标。`command`也就是`make`需要执行的命令。（任意的`Shell`命令）

也就是说，`target`这一个或多个的目标文件依赖于`prerequisites`中的文件，其生成规则定义在`command`中。说白一点就是，`prerequisites`中如果有一个以上的文件比`target`文件要新的话，`command`所定义的命令就会被执行。

### 一个示例

```makefile
edit : main.o kdb.o command.o display.o \
insert.o search.o files.o utils.o
	cc -o edit main.o kbd.o command.o display.o \
	insert.o search.o files.o utils.o

main.o : main.c defs.h
	cc -c main.c

kbd.o : kbd.c defs.h command.h
	cc -c kbd.c

command.o : command.c defs.h command.h
	cc -c command.c

display.o : display.c defs.h buffer.h
	cc -c display.c

insert.o : insert.c defs.h buffer.h
	cc -c insert.c

search.o : search.c defs.h buffer.h
	cc -c search.c

files.o : files.c defs.h buffer.h command.h
	cc -c files.c

utils.o : utils.c defs.h
	cc -c utils.c

clean:
	rm edit main.o kbd.o command.o display.o \
	insert.o search.o files.o utils.o
```

在这个`makefile`中，目标文件（`target`）包含：执行文件`edit`和中间目标文件（`*.o`），依赖文件（`prerequisites`）就是冒号后面的那些`.c`文件和`.h`文件。每一个`.o`文件都有一组依赖文件，而这些`.o`文件又是执行文件`edit`的依赖文件。依赖关系的实质上就是说明了目标文件是由那些文件生成的，换言之，目标文件是哪些文件更新的。

在定义好依赖关系后，后续的那一行定义了如何生成目标文件的操作系统命令，一定要以一个`Tab`键作为开头。`make`并不管命令是怎么工作的，他只管执行所定义的命令。`make`会比较`targets`文件和`prerequisites`文件的修改日期，如果`prerequisites`文件的日期要比`targets`文件的日期要新，或者`targets`不存在的话，那么`make`就会执行后续定义的命令。

`clean`不是一个文件，只是一个动作名字，其冒号后面什么也没有，那么，`make`就不会自动去找文件的依赖性，也就不会自动执行其后定义的命令。

## make是如何工作的

在默认的方式下，也就是我们只输入`make`命令。那么，

1. `make`会在当前目录下找名字叫`makefile`或`Makefile`的文件。

2. 如果找到，它会找文件中的第一个目标文件`target`，在上面的例子中，他会找到`edit`这个文件，并把这个文件作为最终的目标文件。

3. 如果`edit`文件不存在，或是`edit`所依赖的后面的`.o`文件的文件修改时间要比`edit`这个文件新，那么，他就会执行后面所定义的命令来生成`edit`这个文件。

4. 如果`edit`所依赖的`.o`文件也存在，那么`make`会在当前文件中找目标为`.o`文件的依赖性，如果找到则在根据那一规则生成`.o`文件。

   这是整个`make`的依赖性，`make`会一层又一层地去找文件的依赖关系，直到最终编译出第一个目标文件。在找的过程中，如果出现错误，比如最后被依赖的文件找不到，那么`make`就会直接退出，并报错，而对于所定义的命令的错误，或是编译不成功，`make`根本不理。`make`只管文件的依赖性。

## 编译流程

```shell
-E 预处理：把.h .c展开形成一个.i文件。宏定义直接替换 头文件 库文件 
gcc -E hello.c -o hello.i

-S 汇编：.i 生成一个汇编代码文件 .S
gcc -S hello.i -o hello.S

-c 编译：.S 生成一个目标文件 .o .obj
gcc -c hello.S -o hello.o

-o 链接：.o 链接 .exe(windows) .elf(linux) 
gcc hello.o -o hello
```



## 语法

单个`.c`文件编译

```Makefile
hello:hello.o
    gcc hello.o -o hello

hello.o:hello.S
    gcc -c hello.S -o hello.o

hello.S:hello.i
    gcc -S hello.i -o hello.S

hello.i:hello.c
    gcc -E hello.c -o hello.i

.PHONY:
clean:
    rm -rf hello hello.o hello.S hello.i
```

多个文件同路径下

```makefile
main:main.o means.o variance.o
	gcc means.o variance.o main.o -o main

means.o:means.c
	gcc -c means.c -o means.o

variance.o:variance.c
	gcc -c variance.c -o variance.o

main.o:main.c
	gcc -c main.c -o main.o

.PHONY:
cleanall:
	rm -rf main.o means.o variance.o main
clean:
	rm -rf main.o means.o variance.o
```

### 变量

**=（替换） +=（追加） :=（恒等于）**

使用变量$(变量)

```makefile
TARGET = main
OBJ = means.o variance.o main.o
CC := gcc

$(TARGET):main.o means.o variance.o
	$(CC)  $(OBJ) -o $(TARGET)

means.o:means.c
	$(CC) -c means.c -o means.o

variance.o:variance.c
	$(CC) -c variance.c -o variance.o

main.o:main.c
	$(CC) -c main.c -o main.o

.PHONY:
cleanall:
	rm -rf $(OBJ) $(TARGET)
clean:
	rm -rf $(OBJ)
```

### 隐含规则

**%.c %.o *.c *.o**

```makefile
TARGET = main
OBJ = means.o variance.o main.o
CC := gcc

$(TARGET):main.o means.o variance.o
	$(CC)  $(OBJ) -o $(TARGET)
	
%.o:%.c
	$(CC) -c %.c -o %.o
	
.PHONY:
cleanall:
	rm -rf $(OBJ) $(TARGET)
clean:
	rm -rf $(OBJ)
```

### 通配符

**$^  所有的依赖文件**

**$@  所有的目标文件**

**$<所有的依赖文件的第一个文件**

```makefile
TARGET = main
OBJ = means.o variance.o main.o
CC := gcc
RMRF := rm -rf 

$(TARGET):$(OBJ)
	$(CC)  $^ -o $@

%.o:%.c
	$(CC) -c $^ -o $@

.PHONY:
cleanall:
	$(RMRF) $(OBJ) $(TARGET)
clean:
	$(RMRF) $(OBJ)
```





