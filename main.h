#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include <linux/fb.h>

struct FramebufferInfo
{
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    uint8_t *fbp;
    int tty_fd;
    int fb_fd;
};

uint32_t pixel_color(uint8_t r, uint8_t g, uint8_t b, struct fb_var_screeninfo *vinfo);

void render(int x, int y, uint32_t color, struct fb_var_screeninfo *vinfo, struct fb_fix_screeninfo *finfo, uint8_t *fbp);

void initfb(struct FramebufferInfo *fbi);

void cleanfb(struct FramebufferInfo *fbi);

#endif