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
    unsigned width, height;
    struct FramebufferInfo fbi;
    initfb(&fbi);

    unsigned error = lodepng_decode32_file(&image, &width, &height, "./media/background.png");

    if (error)
    {
        fprintf(stderr, "Error %u: %s\n", error, lodepng_error_text(error));
        return 1;
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            uint8_t r = image[4 * width * y + 4 * x + 0];
            uint8_t g = image[4 * width * y + 4 * x + 1];
            uint8_t b = image[4 * width * y + 4 * x + 2];
            // uint8_t a = image[4 * width * y + 4 * x + 3];

            render(x, y, pixel_color(r, g, b, &fbi.vinfo), &fbi.vinfo, &fbi.finfo, fbi.fbp);
        }
    }

    sleep(1);
    free(image);

    return 0;
}