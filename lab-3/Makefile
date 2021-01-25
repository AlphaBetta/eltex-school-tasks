all: pointers_1 pointers_2

pointers_2: pointers_2.o
	gcc -o pointers_2 pointers_2.o

pointers_2.o:
	gcc -c -Wall pointers_2.c

pointers_1: pointers_1.o
	gcc -o pointers_1 pointers_1.o

pointers_1.o:
	gcc -c -Wall pointers_1.c

clean:
	rm pointers_? *.o