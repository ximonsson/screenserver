#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include "xlib.h"

#define DEPTH 			24
#define BITMAP_PAD 		32
#define BYTES_PER_LINE 	 0
#define CHANNELS		 4


static Display*           display;
static Window    		  root_window;
static XWindowAttributes  attributes;
static XImage*            image;


int init_screen_grabbing ()
{
	// initialize connection to display and root window
    display = XOpenDisplay (NULL);
    root_window = DefaultRootWindow (display);
    XGetWindowAttributes (display, root_window, &attributes);
	// create new image to capture to
    image = XGetImage (
		display,
		root_window,
		attributes.x,
		attributes.y,
		attributes.width,
		attributes.height,
		AllPlanes,
		ZPixmap
	);
    return 0;
}

int take_screen_shot (void* buffer)
{
    int 	 x, y;
    long 	 pixel;
    uint8_t* rgba_data = (uint8_t*) buffer;

    // get image from X server
    if (XGetSubImage (
        display,
        root_window,
        attributes.x,
        attributes.y,
        attributes.width,
        attributes.height,
        AllPlanes,
        ZPixmap,
        image,
        0,
        0) == NULL)
    {
        return 1;
    }
    // convert to RGB
    for (y = 0; y < attributes.height; y ++)
        for (x = 0; x < attributes.width; x ++)
        {
            pixel = XGetPixel (image, x, y);
            rgba_data[y * image->width * CHANNELS + x * CHANNELS + 0] = (pixel & image->red_mask) 	>> 16;
            rgba_data[y * image->width * CHANNELS + x * CHANNELS + 1] = (pixel & image->green_mask) >>  8;
            rgba_data[y * image->width * CHANNELS + x * CHANNELS + 2] = (pixel & image->blue_mask);
            rgba_data[y * image->width * CHANNELS + x * CHANNELS + 3] = 0xff;
        }
    return 0;
}

void deinit_screen_grabbing ()
{
    XDestroyImage (image);
}

int screen_width ()
{
    return attributes.width;
}

int screen_height ()
{
    return attributes.height;
}

void screen_dimensions (int* w, int* h)
{
	*w = attributes.width;
	*h = attributes.height;
}
