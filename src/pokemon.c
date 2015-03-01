#include <pebble.h>
void wakeup_handler(WakeupId id, int32_t reason);

static Window *s_main_window;
  
static TextLayer *s_output_layer;
static BitmapLayer *s_image_layer;
static GBitmap *s_icon_bitmap = NULL;
  
//initialization main window
void window_init();
//load/unload main window things
void window_load(Window *window);
void window_unload(Window *window);

static const uint32_t POKEMON_ICONS[] = {
  RESOURCE_ID_vulpix_BLACK,
  RESOURCE_ID_cloyster_BLACK,
  RESOURCE_ID_gengar_BLACK,
  RESOURCE_ID_jolteon_BLACK,
  RESOURCE_ID_pigeot_BLACK,
  RESOURCE_ID_shaymin_BLACK,
  RESOURCE_ID_typh_BLACK,
  RESOURCE_ID_kinman_BLACK
};

char str[128];
  
  
static void init(void) {
     // The app was started by a wakeup
    WakeupId id = 0;
    int32_t reason = 0;
  
  // Create main Window
  window_init();
  
  // Subscribe to Wakeup API
  wakeup_service_subscribe(wakeup_handler);

  // Was this a wakeup launch? This means that it was an encounter
  if (launch_reason() == APP_LAUNCH_WAKEUP) {
    
    strcpy(str, "ENCOUNTERED A POKEMON!");
    
    wakeup_get_launch_event(&id, &reason);
    wakeup_handler(id, reason);
  }
  else{

    strcpy(str, "no pokemon here :(");
    
    // Get details and handle the wakeup
    wakeup_get_launch_event(&id, &reason);
    if(wakeup_query(id, NULL) == false)
    {
      wakeup_handler(id, reason);
      printf("initial start1");
    }
    
    printf("initial start2");
    
  }
}

static void deinit(void) {
  //deallocate all windows
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

//wake up stuff


#define WAKEUP_REASON 0
#define PERSIST_KEY_WAKEUP_ID 42

static WakeupId s_wakeup_id;

void wakeup_handler(WakeupId id, int32_t reason) {
  // The app has woken! set new wake and print new time
   if (!wakeup_query(s_wakeup_id, NULL)) {
    // Current time + 30 seconds
  uint16_t newtime = (rand() % 1800)+1800;
     time_t future_time = time(NULL) + newtime;

    // Schedule wakeup event and keep the WakeupId
    s_wakeup_id = wakeup_schedule(future_time, WAKEUP_REASON, true);
         printf("HERE??????2");
    persist_write_int(PERSIST_KEY_WAKEUP_ID, s_wakeup_id);
         printf("HERE?????3?");
     
   // Delete the ID
  persist_delete(PERSIST_KEY_WAKEUP_ID);
     
         printf("HERE????4??");
   }
 
  if (launch_reason() == APP_LAUNCH_WAKEUP) {
    
    strcpy(str, "ENCOUNTERED A POKEMON");
    printf("does it even get here?");
      if (s_icon_bitmap) {
        gbitmap_destroy(s_icon_bitmap);
      }
      int rand_val = rand() % 8;
      s_icon_bitmap = gbitmap_create_with_resource(POKEMON_ICONS[rand_val]);
      if(s_icon_bitmap != NULL)
      {
      bitmap_layer_set_bitmap(s_image_layer, s_icon_bitmap);
      text_layer_set_text(s_output_layer, str);
      }
      else
      {
      printf("it was null??? why????");
      }
    
    printf("asdfasdfasdfasdfasdfa");
     //VIBRATE!!!
    vibes_double_pulse();
    
  }
  
  else{
    strcpy(str, "no pokemon here :(");

      if (s_icon_bitmap) {
        gbitmap_destroy(s_icon_bitmap);
      }

      text_layer_set_text(s_output_layer, str);
    
    

  }

}

//window stuff here

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
  s_output_layer = text_layer_create(window_bounds);
  text_layer_set_text_alignment(s_output_layer, GTextAlignmentCenter);
  //text_layer_set_text(s_output_layer, str);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
  
    // Create image layer
  s_image_layer =  bitmap_layer_create(window_bounds);
  bitmap_layer_set_background_color(s_image_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_image_layer, GCompOpClear);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_image_layer));
  printf("does the window load?");
}
void window_unload(Window *window) {
  // Destroy output TextLayer
  gbitmap_destroy(s_icon_bitmap);
  text_layer_destroy(s_output_layer);
  bitmap_layer_destroy(s_image_layer);
}

