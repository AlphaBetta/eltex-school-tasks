OPTIONS := -Wall -Wextra -std=c11

all: calculator

calculator: calculator.o mycalc.h libmycalc.a
	gcc -o calculator calculator.o mycalc.h -L. -lmycalc
	
libmycalc.a: add.o sub.o mul.o div.o
	ar rc libmycalc.a add.o sub.o mul.o div.o

add.o: add.c
	gcc $(OPTIONS) -c add.c

sub.o: sub.c
	gcc $(OPTIONS) -c sub.c

mul.o: mul.c
	gcc $(OPTIONS) -c mul.c

div.o: div.c
	gcc $(OPTIONS) -c div.c

calculator.o: calculator.c 
	gcc $(OPTIONS) -c calculator.c

clean:
	rm calculator libmycalc.a *.o
