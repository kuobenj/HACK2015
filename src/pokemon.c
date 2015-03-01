#include <pebble.h>
#include "pokemon.h"
#include "wakeup.h"
#include "window.h"

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
    
    strcpy(str, "ENCOUNTERED BITCH");
    
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