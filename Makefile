CC = gcc
MAIN = main
L = c
OUT = out
O = $(OUT)
CFLAGS-WIN = -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
CFLAGS-LIN = -Llib -lSDL2 -lSDL2_ttf

.SILENT:
all:
	echo "Use specific sys commands listed"
	echo "Winows: build-win"
	echo "LINUX: build-lin"
	echo "Mac: not configured"

build-win:
	mkdir -p out
	$(CC) ./src/$(MAIN).$(L) -o ./$(OUT)/$(MAIN).$(O) $(CFLAGS-WIN)

run-win:
	mkdir -p out
	./$(OUT)/$(MAIN).$(O)

o-win:
	make build-win
	make run-win


build-lin:
	mkdir -p out
	$(CC) ./src/$(MAIN).$(L) -o ./$(OUT)/$(MAIN).$(O) $(CFLAGS-LIN)

run-lin:
	mkdir -p out
	./$(OUT)/$(MAIN).$(O)

o-lin:
	make build-lin
	make run-lin


