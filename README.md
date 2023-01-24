# Digital Clock

## Description
Digital clock made in c using SDL2

Note: Surely to run in windows with gcc/clang/tcc compiler with flags mentioned in the [Makefile](.//Makefile) but dont know about other OS

### Resources:
- [SDL2](https://github.com/libsdl-org/SDL/releases/tag/release-2.26.2)
- [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.1)
- [OpenSans Font](https://fonts.google.com/specimen/Open+Sans?query=Open+Sans)


### Run

#### Windows

```cmd
mkdir -p out
gcc .\src\main.c -o .\out\main.exe -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
.\out\main.exe
```

#### Linux

```sh
mkdir -p out
gcc ./src/main.c -o ./out/main.out -Llib -lSDL2 -lSDL2_ttf
./out/main.out
```

