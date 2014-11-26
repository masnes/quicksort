CFLAGS=-Wall -lm -g
CC=clang
LDFLAGS=
SOURCES=quicksort.c
OBJECTS=
EXECUTABLE=quicksort

all: quicksort

quicksort:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

$@:
	$(CC) $(CFLAGS) $@ -o $@

# .c.o:
	# $(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(SOURCES:.c=) $(OBJECTS) output
