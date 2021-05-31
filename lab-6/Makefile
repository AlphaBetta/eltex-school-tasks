all: phonebook

phonebook: phonebook_dmem.o
	gcc -o phonebook_dmem phonebook_dmem.o

phonebook_dmem.o:
	gcc -c -Wall phonebook_dmem.c

clean:
	rm phonebook *.o