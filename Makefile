CC = cc
CFLAGS = -std=c99
LFLAGS = -lraylib -lm

.PHONY: all clean run

all: gclock

gclock: src/main.c
	$(CC) $< -o $@ $(CFLAGS) $(LFLAGS)

run: gclock
	./gclock
	make clean

clean:
	rm -f ./gclock
