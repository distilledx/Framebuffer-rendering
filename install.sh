mkdir build
gcc ./src/colorsp.c ./src/main.c -o ./build/colorsplash
gcc ./src/imagesp.c ./helpers/lodepng.c ./src/main.c -o ./build/imagesplash

if [ -x "./build/colorsplash" ]; then
    chmod +x ./build/colorsplash
fi

if [ -x "./build/imagesplash" ]; then
    chmod +x ./build/imagesplash
fi
