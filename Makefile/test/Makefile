TARGET = main
OBJ = means.o variance.o main.o
CC := gcc
RMRF := rm -rf 

#$(TARGET):main.o means.o variance.o
#	$(CC)  $(OBJ) -o $(TARGET)

#means.o:means.c
#	$(CC) -c means.c -o means.o

#variance.o:variance.c
#	$(CC) -c variance.c -o variance.o

#main.o:main.c
#	$(CC) -c main.c -o main.o

#%.o:%.c
#	$(CC) -c %.c -o %.o

$(TARGET):$(OBJ)
	$(CC)  $^ -o $@

%.o:%.c
	$(CC) -c $^ -o $@

.PHONY:
cleanall:
	$(RMRF) $(OBJ) $(TARGET)
clean:
	$(RMRF) $(OBJ)