set +x

if [ ! -d "out" ]; then
    mkdir bin
fi

gcc ./src/main.c -o ./out/main.out -Llib -lSDL2 -lSDL2_ttf
./out/main.out