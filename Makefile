CC := gcc
EXC := console\ game1
LIB := -lncurses
all: console\ game1.o
	$(CC) -no-pie console\ game1.o -o $(EXC) $(LIB)

console\ game1.o: console\ game1.c console\ game1.h
	$(CC) -c console\ game1.c
.PHONY: clean
clean:
	rm -rf *.o $(EXC)
