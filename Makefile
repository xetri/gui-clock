CC = cc
CFLAGS = -std=c99
LFLAGS = -lSDL2 -lSDL2_ttf

.PHONY: all clean run

all: gclock

gclock: src/main.c src/*.c src/*.h
	$(CC) $< -o $@ $(CFLAGS) $(LFLAGS)

run: gclock
	./gclock

clean:
	rm -f ./gclock
