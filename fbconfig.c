#include <stdlib.h>
#include <stdio.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>

/* Diagnostic program to display information about 
 * the graphics device 
 * Original developer -- Michael Robbeloth, PDi 2017 */
int main(int argc, char **argv) {  
    struct fb_var_screeninfo vi;

    /* Open either the device path given on the command line or use
     * dev/graphics/fb0 by default */
    int fd;
    if (argc >=2) {
       fd = open(argv[1], O_RDWR);
    }
    else {
       fd = open("/dev/graphics/fb0", O_RDWR);
    }

    /* Verify proper opening of device, abort if something went wrong */
    if (fd < 0) {
       return 1;
    }

    /* Retrieve the variable screen information for the device */
    if (ioctl(fd, FBIOGET_VSCREENINFO, &vi) < 0) {
       close(fd);
       return 2;
    }

    /* Print the variable screen information and terminate */
    printf("fb0 reports:\n"
           "  vi.bits_per_pixel = %d\n"
           "  vi.red.offset   = %3d   .length = %3d\n"
           "  vi.green.offset = %3d   .length = %3d\n"
           "  vi.blue.offset  = %3d   .length = %3d\n"
           "  vi.transp.offset = %3d  .length = %3d\n"
           "  vi.pixclock = %6d\n"
           "  vi.xres=%4d vi.yres=%4d\n"
           "  vi.xres_virutal=%4d vi.yres_virtual=%4d\n"
           "  vi.xoffset=%4d vi.yoffset=%4d\n"
           "  vi.nonstd=%3d\n"
           "  vi.activate=%3d\n"
           "  vi.height=%4d mm \n vi.width=%4d mm \n"
           "  vi.left_margin=%4d vi.right_margin=%4d\n"
           "  vi.upper_margin=%4d vi.lower_margin=%4d\n"
           "  vi.hsync_len=%4d vi.vsync_len=%4d\n"
           "  vi.vmode=%3d\n"
           "  vi.rotate=%3d\n",
           vi.bits_per_pixel,
           vi.red.offset, vi.red.length,
           vi.green.offset, vi.green.length,
           vi.blue.offset, vi.blue.length,
           vi.transp.offset, vi.transp.length,
           vi.pixclock,
           vi.xres, vi.yres, 
           vi.xres_virtual, vi.yres_virtual,
           vi.xoffset, vi.yoffset, 
           vi.nonstd,
           vi.activate,
           vi.height, vi.width,
           vi.left_margin, vi.right_margin,
           vi.upper_margin, vi.lower_margin,
           vi.hsync_len, vi.vsync_len, 
           vi.vmode,
           vi.rotate);

    /* Return successful completion */
    return 0;
}
