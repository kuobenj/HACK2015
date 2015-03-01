#pragma once
  
static Window *s_main_window;
  
static TextLayer *s_output_layer;
static BitmapLayer *s_image_layer;
  
//initialization main window
void window_init();
//load/unload main window things
static void window_load(Window *window);
static void window_unload(Window *window);

char str[128];