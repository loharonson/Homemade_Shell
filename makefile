.PHONY: clean run compile
run: turtling
	@./turtling
compile turtling: main.o parse.o reading.o operations.o
	@gcc -o turtling main.o parse.o reading.o operations.o
main.o: main.h main.c
	@gcc -c main.c
parse.o: parse.c parse.h
	@gcc -c parse.c
reading.o: reading.c reading.h
	@gcc -c reading.c
operations.o: operations.c operations.h
	@gcc -c operations.c
clean:
	rm -f *.o turtling
