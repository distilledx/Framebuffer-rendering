//   ____      _            ____        _           _
//  / ___|___ | | ___  _ __/ ___| _ __ | | __ _ ___| |__
// | |   / _ \| |/ _ \| '__\___ \| '_ \| |/ _` / __| '_ \ 
// | |__| (_) | | (_) | |   ___) | |_) | | (_| \__ \ | | |
//  \____\___/|_|\___/|_|  |____/| .__/|_|\__,_|___/_| |_|
//                               |_|
//
// Display a full screen of a single color

#include "./src/main.h"
#include <unistd.h>

int main()
{
    struct FramebufferInfo fbi;
    initfb(&fbi);

    int x, y;

    for (x = 0; x < fbi.vinfo.xres; x++)
        for (y = 0; y < fbi.vinfo.yres; y++)
        {
            render(x, y, pixel_color(0xFF, 0xCF, 0xCF, &fbi.vinfo), &fbi.vinfo, &fbi.finfo, fbi.fbp);
        }

    sleep(1);
    cleanfb(&fbi);

    return 0;
}