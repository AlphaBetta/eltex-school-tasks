OPTIONS := -Wall -Wextra -std=c11

all: calculator dlibs

calculator: calculator.o
	gcc -ldl -o calculator calculator.o 
	
dlibs: addition.so subtraction.so multiplication.so division.so

addition.so: addition.o
	gcc --shared -o addition.so addition.o

subtraction.so: subtraction.o
	gcc --shared -o subtraction.so subtraction.o

multiplication.so: multiplication.o
	gcc --shared -o multiplication.so multiplication.o

division.so: division.o
	gcc --shared -o division.so division.o

addition.o: addition.c
	gcc $(OPTIONS) -fPIC -c addition.c

subtraction.o: subtraction.c
	gcc $(OPTIONS) -fPIC -c subtraction.c

multiplication.o: multiplication.c
	gcc $(OPTIONS) -fPIC -c multiplication.c

division.o: division.c
	gcc $(OPTIONS) -fPIC -c division.c

calculator.o: calculator.c 
	gcc $(OPTIONS) -c calculator.c

clean:
	rm calculator *.so *.o
