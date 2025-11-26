.PHONY: clean run compile
run: turtling
	@./turtling
compile turtling: main.o parse.o reading.o
	@gcc -o turtling main.o parse.o reading.o
main.o: main.h main.c
	@gcc -c main.c
parse.o: parse.c parse.h
	@gcc -c parse.c
reading.o: reading.c reading.h
	@gcc -c reading.c
clean:
	rm -f *.o turtling
