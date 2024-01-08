CC = gcc
FLAGS = -W -Wall -Wpedantic -g
PROGRAMS = snake

all: $(PROGRAMS)

snake: snake.o $(OBJECTS)
	$(CC) $(FLAGS) -o $@ $^

snake.o: snake.c
 
clean:
	rm -f $(PROGRAMS) *.o $(OBJECTS)
