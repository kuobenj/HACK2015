#include <pebble.h>
#include "window.h"
  
void window_init(){
   // Create main Window
  s_main_window = window_create();
  //window_set_click_config_provider(s_main_window, click_config_provider);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_main_window, true);
}
  
void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create output TextLayer
  s_output_layer = text_layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  text_layer_set_text_alignment(s_output_layer, GTextAlignmentCenter);
  text_layer_set_text(s_output_layer, str);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
  
    // Create image layer
  s_image_layer =  bitmap_layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  //figure out image specifics here
}
static void window_unload(Window *window) {
  // Destroy output TextLayer
  text_layer_destroy(s_output_layer);
  bitmap_layer_destroy(s_image_layer);
}