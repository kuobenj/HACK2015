#include <pebble.h>
#include "wakeup.h"
#include "window.h"

#define WAKEUP_REASON 0
#define PERSIST_KEY_WAKEUP_ID 42

static WakeupId s_wakeup_id;

void wakeup_handler(WakeupId id, int32_t reason) {
  // The app has woken! set new wake and print new time
  
  uint8_t newtime = (rand() % 15)+10;
 
  //static char s_buffer[128];

  
  
  //snprintf(s_buffer, sizeof(s_buffer), "WAKE UP!!! next wake in %d seconds", newtime);
  
  //text_layer_set_text(s_output_layer, s_buffer);
  
  //window_stack_push(s_encounter_window, true);
  
        // Current time + random seconds
    time_t future_time = time(NULL) + newtime;
  
    s_wakeup_id = wakeup_schedule(future_time, WAKEUP_REASON, true);
    persist_write_int(PERSIST_KEY_WAKEUP_ID, s_wakeup_id);
  
  //VIBRATE!!!
  vibes_double_pulse();
  
  // Delete the ID
  persist_delete(PERSIST_KEY_WAKEUP_ID);
}

// static void check_wakeup() {
//   // Get the ID
//   s_wakeup_id = persist_read_int(PERSIST_KEY_WAKEUP_ID);

//   if (s_wakeup_id > 0) {
//     // There is a wakeup scheduled soon
//     time_t timestamp = 0;
//     wakeup_query(s_wakeup_id, &timestamp);
//     int seconds_remaining = timestamp - time(NULL);

//     // Show how many seconds to go
//     static char s_buffer[64];
//     snprintf(s_buffer, sizeof(s_buffer), "The event is already scheduled for %d seconds from now!", seconds_remaining);
//     text_layer_set_text(s_output_layer, s_buffer);
//   }
// }

// static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
//   //Check the event is not already scheduled
//   if (!wakeup_query(s_wakeup_id, NULL)) {
//     // Current time + 30 seconds
//     time_t future_time = time(NULL) + 30;

//     // Schedule wakeup event and keep the WakeupId
//     s_wakeup_id = wakeup_schedule(future_time, WAKEUP_REASON, true);
//     persist_write_int(PERSIST_KEY_WAKEUP_ID, s_wakeup_id);

//     // Prepare for waking up later
//     text_layer_set_text(s_output_layer, "This app will now wake up in 30 seconds.\n\nClose me!");
//   } else {
//     // Check existing wakeup
//     check_wakeup();
//   }
// }

// static void click_config_provider(void *context) {
//   // Register the ClickHandlers
//   window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
// }



//not needed I think
static void deinit(void) {
//nothing
}
