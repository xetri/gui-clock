CC = gcc
MAIN = main
L = c
OUT = out
CFLAGS = -Wall -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

build:
	$(CC) src/$(MAIN).$(L) -o $(OUT)/$(MAIN).$(OUT) $(CFLAGS)

run:
	./$(OUT)/$(MAIN).$(OUT)

o:
	make build
	make run

init:
	curl https://github.com/libsdl-org/SDL/releases/download/release-2.26.2/SDL2-devel-2.26.2-mingw.zip > SDL2.zip
	curl https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.1/SDL2_ttf-devel-2.20.1-mingw.zip > SDL2_ttf.zip
	curl https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.2/SDL2_image-devel-2.6.2-mingw.zip > SDL2_image.zip
