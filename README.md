# Framebuffer rendering

This uses the framebuffer device available on linux devices to draw pixels on the screen.

This project doesn't use any userspace libraries and only uses libc calls that 1-1 map to system calls.
To run, you'll need sudo permissions as it accesses `/dev`.

-   [x] Display fullscreen splashes
-   [ ] Read and map pixel data from an image
-   [ ] Read and map pixel data from a gif
-   [ ] Read data from a gif and make it translate across the screen
