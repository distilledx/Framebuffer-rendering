# Framebuffer rendering

This uses the framebuffer device available on linux devices to draw pixels on the screen.

This project doesn't use any userspace libraries and only uses libc calls that 1-1 map to system calls.
To run, you'll need sudo permissions as it accesses `/dev`.

To actually view the output of the code, you will need to switch your virtual terminal. This is the result of probably having a program running that uses the framebuffer, such as X.

To switch your virtual terminal, press ctrl+alt+f3 (or any fn key other than 1,2. Those probably map to a GUI terminal on a modern system. To know exactly, check your distribution documentation). You can always return to your desktop using ctrl+alt+f1 (again, might differ by distribution).

-   [x] Display fullscreen splashes
-   [ ] Read and map pixel data from an image
-   [ ] Read and map pixel data from a gif
-   [ ] Read data from a gif and make it translate across the screen
