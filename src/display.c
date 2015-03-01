#include "pebble.h"

static Window *window;

static TextLayer *encounter_layer;
static char temperature[25];

static TextLayer *name_layer;
static char test[25];

static BitmapLayer *icon_layer;
static GBitmap *icon_bitmap = NULL;

static AppSync sync;
static uint8_t sync_buffer[64];

char strings[10][50] = {
  "Encountered a wild Gengar!",
  "Can't touch this... dun na na na",
  "Fuck Yeah",
  "i know where u live"
};

enum displayKeys {
  SPRITE_KEY = 0x0,         // TUPLE_INT
  ENCOUNTER_KEY = 0x1,  // TUPLE_CSTRING
  NAME_KEY = 0x2,
};

static uint32_t picIcons[] = {
  RESOURCE_ID_gengar,
  RESOURCE_ID_gengar,
  RESOURCE_ID_bulbasaur,
  RESOURCE_ID_shaymin
};

static void sync_error_callback(DictionaryResult dict_error, AppMessageResult app_message_error, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Sync Error: %d", app_message_error);
}

static void sync_tuple_changed_callback(const uint32_t key, const Tuple* new_tuple, const Tuple* old_tuple, void* context) {
  switch (key) {
    case SPRITE_KEY:
      if (icon_bitmap) {
        gbitmap_destroy(icon_bitmap);
      }

      icon_bitmap = gbitmap_create_with_resource(picIcons[new_tuple->value->uint8]);
      bitmap_layer_set_bitmap(icon_layer, icon_bitmap);
      break;

    case ENCOUNTER_KEY:
      // App Sync keeps new_tuple in sync_buffer, so we may use it directly
      text_layer_set_text(encounter_layer, new_tuple->value->cstring);
      break;
      
    case NAME_KEY:
      text_layer_set_text(name_layer, new_tuple->value->cstring);
      break;
  }
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  // icon_layer = bitmap_layer_create(GRect(72, 0, 72, 84));
  icon_layer = bitmap_layer_create(GRect(72, 0, 80, 84));
  layer_add_child(window_layer, bitmap_layer_get_layer(icon_layer));

  // encounter_layer = text_layer_create(GRect(0, 80, 144, 25));
  encounter_layer = text_layer_create(GRect(0, 80, 100, 50));
  text_layer_set_text_color(encounter_layer, GColorBlack);
  text_layer_set_background_color(encounter_layer, GColorWhite);
  //text_layer_set_font(encounter_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(encounter_layer, GTextAlignmentCenter);
  text_layer_set_text(encounter_layer, temperature);
  text_layer_set_overflow_mode(encounter_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(encounter_layer));

  // name_layer = text_layer_create(GRect(0, 125, 144, 25));
  name_layer = text_layer_create(GRect(0, 150, 130, 25));
  text_layer_set_text_color(name_layer, GColorWhite);
  text_layer_set_background_color(name_layer, GColorWhite);
  //text_layer_set_font(name_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(name_layer, GTextAlignmentCenter);
  text_layer_set_text(name_layer, test);
  layer_add_child(window_layer, text_layer_get_layer(name_layer));

  
  Tuplet initial_values[] = {
    TupletInteger(SPRITE_KEY, (uint8_t) 0),
    TupletCString(ENCOUNTER_KEY, strings[3]),
//     TupletCString(NAME_KEY, "suuuup"),
  };
  app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values, ARRAY_LENGTH(initial_values),
      sync_tuple_changed_callback, sync_error_callback, NULL);

}

static void window_unload(Window *window) {
  app_sync_deinit(&sync);

  if (icon_bitmap) {
    gbitmap_destroy(icon_bitmap);
  }

  text_layer_destroy(name_layer);
  text_layer_destroy(encounter_layer);
  bitmap_layer_destroy(icon_layer);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(encounter_layer, strings[rand()%4]);
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
//   window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
//   window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void init() {
  window = window_create();
  window_set_background_color(window, GColorClear);
  window_set_fullscreen(window, true);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });
  
  window_set_click_config_provider(window, click_config_provider);

  // const int inbound_size = 64;
  // const int outbound_size = 16;
  // app_message_open(inbound_size, outbound_size);

  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit() {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
                  