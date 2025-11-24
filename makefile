CC = gcc

CFLAGS = -std=c11

LDFLAGS =

SRCS = main.c parse.c

HEADERS = main.h parse.h

TARGET = main

run: $(TARGET)
	@./$(TARGET)

compile: $(TARGET)

$(TARGET): $(SRCS:.c=.o)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f *.o $(TARGET)

.PHONY: compile run clean
