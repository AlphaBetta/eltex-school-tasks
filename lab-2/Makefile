all: arrays_1 arrays_2

arrays_2: arrays_2.o
	gcc -o arrays_2 arrays_2.o

arrays_2.o:
	gcc -c -Wall arrays_2.c

arrays_1: arrays_1.o
	gcc -o arrays_1 arrays_1.o

arrays_1.o:
	gcc -c -Wall arrays_1.c

clean:
	rm arrays_? *.o
