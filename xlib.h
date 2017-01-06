#include <stdint.h>

int  init_screen_grabbing () ;
int  take_screen_shot (void*) ;
void deinit_screen_grabbing () ;
int  screen_width () ;
int  screen_height () ;
void screen_dimensions (int* w, int* h);
