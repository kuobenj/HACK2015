#include <pebble.h>
#include "pokemon.h"
#include "wakeup.h"
#include "window.h"

static void init(void) {
  // Subscribe to Wakeup API
  wakeup_service_subscribe(wakeup_handler);

  // Was this a wakeup launch? This means that it was an encounter
  if (launch_reason() == APP_LAUNCH_WAKEUP) {
    // The app was started by a wakeup
    WakeupId id = 0;
    int32_t reason = 0;

    strcpy(str, "ENCOUNTERED BITCH");
    
    // Get details and handle the wakeup
    wakeup_get_launch_event(&id, &reason);
    wakeup_handler(id, reason);
  }
  else{
    // The app was started by a wakeup
    WakeupId id = 0;
    int32_t reason = 0;

    // Get details and handle the wakeup
    wakeup_get_launch_event(&id, &reason);
    if(wakeup_query(id, NULL) == false)
    {
      wakeup_handler(id, reason);
    }
    
    strcpy(str, "no pokemon");
    
  }
  
  // Create main Window
  window_init();
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