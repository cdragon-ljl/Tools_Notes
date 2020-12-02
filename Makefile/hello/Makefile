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


