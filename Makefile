CC = gcc
MAIN = main
L = c
OUT = out
O = $(OUT)
CFLAGS = -Wall -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

build:
	mkdir -p out
	$(CC) ./src/$(MAIN).$(L) -o ./$(OUT)/$(MAIN).$(O) $(CFLAGS)

run:
	mkdir -p out
	./$(OUT)/$(MAIN).$(O)

o:
	make build
	make run
