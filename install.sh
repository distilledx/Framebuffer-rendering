mkdir build
gcc ./src/colorsp.c ./src/main.c -o ./build/colorsplash
gcc ./src/imagesp.c ./helpers/lodepng.c ./src/main.c -o ./build/imagesplash
gcc ./src/gifsp.c ./src/main.c  -o ./build/gifsplash -lgif

if [ -x "./build/colorsplash" ]; then
    chmod +x ./build/colorsplash
fi

if [ -x "./build/imagesplash" ]; then
    chmod +x ./build/imagesplash
fi

if [ -x "./build/gifsplash" ]; then
    chmod +x ./build/gifsplash
fi
