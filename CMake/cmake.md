# CMake

**文件名称CMakeLists.txt**

## 单个源文件

```c++
#include <iostream>
using namespace std;

int main(void) {
    cout << "Hello World" << endl;
    return 0;
}
```

**编写CMakeLists.txt，并保存在与main.c源文件同个目录下**

```cmake
# CMake 最低版本号要求
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

# 项目信息
PROJECT (Demo1)

# 指定生成目标
ADD_EXECUTABLE (Demo1 main.cpp)
```

**CMakeLists.txt的语法由命令、注释、和空格组成，命令不区分大小写。符号#后面的内容被认为是注释。命令由命令名称、小括号和参数组成，参数之间使用空格进行间隔。**

对于上面的CMakeLists.txt文件，依次出现了几个命令：

1. `CMAKE_MINIMUM_REQUIRED`:指定运行此配置文件所需的CMake的最低版本；
2. `PROJECT`:参数值是Demo，该命令表示项目的名称是Demo；
3. `ADD_EXECUTABLE`：将名为main.cpp的源文件编译成一个名称为Demo1的可执行文件。

**编译项目**

**在当前目录执行`cmake .`，得到Makefile后再使用`make`命令编译得到Demo1可执行文件。**

## 多个源文件

### 同一目录，多个源文件

```dir
./demo2
	|
	+---demo2.cpp
	|
	+---add.cpp
	|
	+---add.h
```

这时候，CMakeLists.txt可以改成如下的形式：

```cmake
# CMake 最低版本号要求
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

# 项目信息
PROJECT (Demo2)

# 指定生成目标
ADD_EXECUTABLE (demo2 demo2.cpp add.cpp)
```

唯一 改动只是在`ADD_EXECUTABLE`命令中增加了一个`add.cpp`源文件。但是如果源文件很多，更省事的方法是使用`AUX_SOURCE_DIRECTORY`命令，该命令会查找指定目录下的所有源文件，然后将结果存进指定变量名。

因此，可以修改CMakeList.txt如下：

```cmake
# CMake 最低版本号要求
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

# 项目信息
PROJECT (Demo2)

# 查找当前目录下的所有源文件 并将名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY (. DIR_SRCS)

# 指定生成目标
ADD_EXECUTABLE (demo2 ${DIR_SRCS})
```

这样，CMake会将当前目录所有源文件的文件名赋值给变量`DIR_SRCS`，再指示变量`DIR_SRCS`中的源文件需要编译成一个名称为`demo2`的可执行文件。

### 多个目录，多个源文件

```dir
./Demo3
	|
	+---demo3.cpp
	|
	+---add/
		|
		+---add.cpp
		|
		+---add.h
```

对于这种情况，需要分别在项目根目录`Demo3`和`add`目录里各编写一个`CMakeLists.txt`文件。为了方便，可以先将`add`目录里的文件编译成静态库再由`main`函数调用。

根目录中的`CMakeLists.txt`：

```cmake
# CMake 最低版本号要求
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

# 项目信息
PROJECT (Demo3)

# 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY (. DIR_SRCS)

# 添加 add 子目录
ADD_SUBDIRECTORY (add)

# 指定生成目标
ADD_EXECUTABLE (demo3 demo3.cpp)

# 添加链接库
TARGET_LINK_LIBRARIES (demo3 AddFunctions)
```

子目录中的`CMakeLists.txt`:

```cmake
# 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY (. DIR_LIB_SRCS)

# 生成链接库
ADD_LIBRARY (AddFunctions ${DIR_LIB_SRCS})
```

