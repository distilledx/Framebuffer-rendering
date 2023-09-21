# Framebuffer rendering

This uses the framebuffer device available on linux devices to draw pixels on the screen.

This project doesn't use any userspace libraries and only uses libc calls that 1-1 map to system calls for rendering.
To run, you'll need sudo permissions as it accesses `/dev`.

To actually view the output of the code, you will need to switch your virtual terminal. The program renders on /dev/tty2 by default as to not lock tty0 in case of any (unlikely) problems.

To switch your virtual terminal to tty2, press ctrl+alt+f3. You can always return to your desktop using ctrl+alt+f1 (might differ by distribution).

To clear any artifacts from your virtual terminal, just type `clear`.

-   [x] Display fullscreen splashes
-   [x] Read and map pixel data from an image (partial transparency not supported. default modes on most framebuffers don't assign a byte for this)
-   [x] Read and map pixel data from a gif (Requires `giflib` package. Some GIFs either do not display properly or don't display at all. This is unimportant as the point of this project was to learn about the framebuffer, and not GIF decoding ;) )

### Building

Run `./install.sh`. Go to the `build` directly and execute any of the files.

OR

`gcc ./src/colorsp.c ./src/main.c -o ./build/colorsplash` for displaying fullscreen splashes of a single color.

`gcc ./src/imagesp.c ./helpers/lodepng.c ./src/main.c -o ./build/imagesplash` for displaying an image.

`gcc ./src/gifsp.c ./src/main.c  -o ./build/gifsp -lgif` for displaying 5 iterations of a gif.

### Running

`cd build` before running. All executables need `sudo` permissions as they access `/dev/fb0` and `/dev/tty2`.

To set a custom image, replace `media/image.png` with your own `PNG` file and rename it `image.png` (similarly with gifs).

Eg: `build$ sudo ./imagesplash`
