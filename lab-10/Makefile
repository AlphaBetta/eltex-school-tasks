OPTIONS := -Wall -Wextra -std=c11

all: read_from_EOF

read_from_EOF: read_from_EOF.c
	gcc $(OPTIONS) -o read_from_EOF read_from_EOF.c

clean:
	rm read_from_EOF test.txt