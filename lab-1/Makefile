all: bitwise_operations_1 bitwise_operations_2

bitwise_operations_2: bitwise_operations_2.o
	gcc -o bitwise_operations_2 bitwise_operations_2.o

bitwise_operations_2.o:
	gcc -c -Wall bitwise_operations_2.c

bitwise_operations_1: bitwise_operations_1.o
	gcc -o bitwise_operations_1 bitwise_operations_1.o

bitwise_operations_1.o:
	gcc -c -Wall bitwise_operations_1.c

clean:
	rm bitwise_operations_1 bitwise_operations_2 *.o
