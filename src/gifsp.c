#include <stdio.h>
#include <stdint.h>
#include <gif_lib.h>
#include <time.h>
#include "main.h"

struct pixel
{
    int x;
    int y;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

int frameDelay = 0;

int main()
{
    unsigned char *image;
    int width, height, startx, starty;

    struct FramebufferInfo fbi;
    initfb(&fbi);

    GifFileType *gif = DGifOpenFileName("../media/gif.gif", NULL);
    if (gif == NULL)
    {
        fprintf(stderr, "Error opening GIF file\n");
        return 1;
    }

    int x = DGifSlurp(gif);

    struct pixel frames[gif->ImageCount][gif->SWidth * gif->SHeight];
    int pixnum = 0;
    for (int i = 0; i < gif->ImageCount; i++)
    {
        pixnum = 0;
        SavedImage sp = gif->SavedImages[i];
        ColorMapObject *colorMap = (sp.ImageDesc.ColorMap != NULL) ? sp.ImageDesc.ColorMap : gif->SColorMap;
        GifPixelType *rasterBits = sp.RasterBits;

        if (sp.ExtensionBlocks->ByteCount == 4)
        {
            frameDelay = ((sp.ExtensionBlocks->Bytes[1]) | ((sp.ExtensionBlocks->Bytes[2]) << 8));
        }

        for (int j = 0; j < sp.ImageDesc.Height; j++)
        {
            for (int k = 0; k < sp.ImageDesc.Width; k++)
            {
                pixnum++;
                GifPixelType pixelIndex = rasterBits[j * sp.ImageDesc.Width + k];
                GifColorType color = colorMap->Colors[pixelIndex];

                uint8_t red = color.Red;
                uint8_t green = color.Green;
                uint8_t blue = color.Blue;

                struct pixel p = {k, j, red, green, blue};
                frames[i][pixnum] = p;
            }
        }
    }

    width = gif->SWidth;
    height = gif->SHeight;
    startx = (0 > ((int)fbi.vinfo.xres - width) / 2) ? 0 : ((int)fbi.vinfo.xres - width) / 2;
    starty = (0 > ((int)fbi.vinfo.yres - height) / 2) ? 0 : ((int)fbi.vinfo.yres - height) / 2;
    width = ((int)fbi.vinfo.xres < width) ? (int)fbi.vinfo.xres : width;
    height = ((int)fbi.vinfo.yres < height) ? (int)fbi.vinfo.yres : height;

    struct timespec remaining, request;
    request.tv_sec = 0;
    request.tv_nsec = frameDelay * 10000000;
    int iterations = 5;

    for (int n = 0; n < iterations; n++)
    {
        for (int i = 0; i < gif->ImageCount; i++)
        {
            for (int j = 0; j < width * height; j++)
            {
                render(startx + frames[i][j].x, starty + frames[i][j].y, pixel_color(frames[i][j].r, frames[i][j].g, frames[i][j].b, &fbi.vinfo), &fbi.vinfo, &fbi.finfo, fbi.fbp);
            }
            nanosleep(&request, &remaining);
        }
    }
    cleanfb(&fbi);
}
