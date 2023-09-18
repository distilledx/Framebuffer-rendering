# Framebuffer rendering

This uses the framebuffer device available on linux devices to draw pixels on the screen.

This project doesn't use any userspace libraries and only uses libc calls that 1-1 map to system calls for rendering.
To run, you'll need sudo permissions as it accesses `/dev`.

To actually view the output of the code, you will need to switch your virtual terminal. The program renders on /dev/tty2 by default as to not lock tty0 in case of any (unlikely) problems.

To switch your virtual terminal to tty2, press ctrl+alt+f3. You can always return to your desktop using ctrl+alt+f1 (might differ by distribution).

To clear any artifacts from your virtual terminal, just type `clear`.

-   [x] Display fullscreen splashes
-   [ ] Read and map pixel data from an image
-   [ ] Read and map pixel data from a gif
-   [ ] Read data from a gif and make it translate across the screen
