#include <fcntl.h>
#include <linux/fb.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <time.h>
#include <linux/kd.h>
#include <unistd.h>
#include "main.h"

uint32_t pixel_color(uint8_t r, uint8_t g, uint8_t b, struct fb_var_screeninfo *vinfo)
{
    return (r << vinfo->red.offset) | (g << vinfo->green.offset) | (b << vinfo->blue.offset);
}

void render(int x, int y, uint32_t color, struct fb_var_screeninfo *vinfo, struct fb_fix_screeninfo *finfo, uint8_t *fbp)
{
    long location = (x + vinfo->xoffset) * (vinfo->bits_per_pixel / 8) + (y + vinfo->yoffset) * finfo->line_length;
    *((uint32_t *)(fbp + location)) = color;
}

void cleanfb(struct FramebufferInfo *fbi)
{
    ioctl(fbi->tty_fd, KDSETMODE, KD_TEXT);
    munmap(fbi->fbp, fbi->vinfo.yres_virtual * fbi->finfo.line_length);
    close(fbi->fb_fd);
    close(fbi->tty_fd);
}

void initfb(struct FramebufferInfo *fbi)
{
    fbi->tty_fd = open("/dev/tty2", O_RDWR);
    ioctl(fbi->tty_fd, KDSETMODE, KD_GRAPHICS);
    fbi->fb_fd = open("/dev/fb0", O_RDWR);
    ioctl(fbi->fb_fd, FBIOGET_FSCREENINFO, &fbi->finfo);
    ioctl(fbi->fb_fd, FBIOGET_VSCREENINFO, &fbi->vinfo);
    fbi->vinfo.grayscale = 0;
    fbi->vinfo.bits_per_pixel = 32;
    ioctl(fbi->fb_fd, FBIOPUT_VSCREENINFO, &fbi->vinfo);
    ioctl(fbi->fb_fd, FBIOGET_VSCREENINFO, &fbi->vinfo);

    long screensize = fbi->vinfo.yres_virtual * fbi->finfo.line_length;
    fbi->fbp = mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbi->fb_fd, (off_t)0);
}