CFLAGS=-Wall -lm -g -pthreads
CC=clang
LDFLAGS=
SOURCES=quicksort.c
OBJECTS=
EXECUTABLE=quicksort

all: quicksort

quicksort: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

$@:
	$(CC) $(CFLAGS) $@ -o $@

# .c.o:
	# $(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(SOURCES:.c=) $(OBJECTS) output

