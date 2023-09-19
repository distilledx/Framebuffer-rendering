//  ___                            ____        _           _
// |_ _|_ __ ___   __ _  __ _  ___/ ___| _ __ | | __ _ ___| |__
//  | || '_ ` _ \ / _` |/ _` |/ _ \___ \| '_ \| |/ _` / __| '_ \ 
//  | || | | | | | (_| | (_| |  __/___) | |_) | | (_| \__ \ | | |
// |___|_| |_| |_|\__,_|\__, |\___|____/| .__/|_|\__,_|___/_| |_|
//                      |___/           |_|

// Displays a single image

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "./helpers/lodepng.h"
#include "./src/main.h"
#include <unistd.h>

int main()
{
    unsigned char *image;
    int width, height, startx, starty, endx, endy;

    struct FramebufferInfo fbi;
    initfb(&fbi);

    unsigned error = lodepng_decode32_file(&image, &width, &height, "./media/image.png");

    if (error)
    {
        fprintf(stderr, "Error %u: %s\n", error, lodepng_error_text(error));
        return 1;
    }

    startx = (0 > ((int)fbi.vinfo.xres - width) / 2) ? 0 : ((int)fbi.vinfo.xres - width) / 2;
    starty = (0 > ((int)fbi.vinfo.yres - height) / 2) ? 0 : ((int)fbi.vinfo.yres - height) / 2;
    int dis_width = ((int)fbi.vinfo.xres < width) ? (int)fbi.vinfo.xres : width;
    int dis_height = ((int)fbi.vinfo.yres < height) ? (int)fbi.vinfo.yres : height;

    for (int y = 0; y < dis_height; y++)
    {
        for (int x = 0; x < dis_width; x++)
        {
            uint8_t r = image[4 * width * y + 4 * x + 0];
            uint8_t g = image[4 * width * y + 4 * x + 1];
            uint8_t b = image[4 * width * y + 4 * x + 2];
            uint8_t a = image[4 * width * y + 4 * x + 3];

            if ((int)a < 255)
                continue;

            render(startx + x, starty + y, pixel_color(r, g, b, &fbi.vinfo), &fbi.vinfo, &fbi.finfo, fbi.fbp);
        }
    }

    sleep(3);
    free(image);
    cleanfb(&fbi);

    return 0;
}