CC = gcc
MAIN = main
L = c
OUT = out
O = exe
CFLAGS = -Wall -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

build:
	$(CC) src/$(MAIN).$(L) -o $(OUT)/$(MAIN).$(O) $(CFLAGS)

run:
	./$(OUT)/$(MAIN).$(O)

o:
	make build
	make run