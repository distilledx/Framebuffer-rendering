#include <stdio.h>
#include <gif_lib.h>

int main()
{
    GifFileType *gif = DGifOpenFileName("../media/gif.gif", NULL);
    if (gif == NULL)
    {
        fprintf(stderr, "Error opening GIF file\n");
        return 1;
    }

    int x = DGifSlurp(gif);
    for (int i = 0; i < gif->ImageCount; i++)
    {
        ColorMapObject *colorMap = gif->SavedImages[i].ImageDesc.ColorMap;
        GifPixelType *rasterBits = gif->SavedImages[i].RasterBits;

        for (int j = 0; j < gif->SavedImages[i].ImageDesc.Height; j++)
        {
            for (int k = 0; k < gif->SavedImages[i].ImageDesc.Width; k++)
            {
                GifPixelType pixelIndex = rasterBits[j * gif->SavedImages[i].ImageDesc.Width + k];
                GifColorType color = colorMap->Colors[pixelIndex];

                unsigned char red = color.Red;
                unsigned char green = color.Green;
                unsigned char blue = color.Blue;
                unsigned char alpha = 255;

                // Print RGBA values
                printf("Frame %d, Pixel (%d, %d): RGBA(%d, %d, %d, %d)\n",
                       i, j, k, red, green, blue, alpha);
            }
        }
    }
}