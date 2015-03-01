#pragma once
  
static Window *s_main_window;
  
static TextLayer *s_output_layer;
static BitmapLayer *s_image_layer;
static GBitmap *s_icon_bitmap = NULL;
  
//initialization main window
void window_init();
//load/unload main window things
static void window_load(Window *window);
static void window_unload(Window *window);

static const uint32_t POKEMON_ICONS[] = {
  RESOURCE_ID_vulpix,
  RESOURCE_ID_vulpix,
  RESOURCE_ID_vulpix,
  RESOURCE_ID_vulpix,
};

char str[128];
