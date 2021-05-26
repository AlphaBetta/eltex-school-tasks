
all: structs_1 structs_2

structs_2: structs_2.o
	gcc -o structs_2 structs_2.o

structs_2.o:
	gcc -c -Wall structs_2.c

structs_1: structs_1.o
	gcc -o structs_1 structs_1.o

structs_1.o:
	gcc -c -Wall structs_1.c

clean:
	rm structs_? *.o