OPTIONS := -Wall -Wextra -std=c11

all: calculator

calculator: calculator.o mycalc.h libmycalc.so
	gcc -o calculator calculator.o mycalc.h -L. -Wl,-rpath=/home/epsilon/Eltex/eltex-school-tasks/lab-8 -lmycalc 
	
libmycalc.so: add.o sub.o mul.o div.o
	gcc --shared -o libmycalc.so add.o sub.o mul.o div.o

add.o: add.c
	gcc $(OPTIONS) -fPIC -c add.c

sub.o: sub.c
	gcc $(OPTIONS) -fPIC -c sub.c

mul.o: mul.c
	gcc $(OPTIONS) -fPIC -c mul.c

div.o: div.c
	gcc $(OPTIONS) -fPIC -c div.c

calculator.o: calculator.c 
	gcc $(OPTIONS) -c calculator.c

clean:
	rm calculator libmycalc.so *.o
