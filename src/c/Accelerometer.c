#include <pebble.h>

static Window *s_window;
// static TextLayer *s_text_layer;

static void click_config_provider(void *context) {

}

static void raw_data_handler(AccelRawData *data, uint32_t num_samples, uint64_t timestamp) {
  APP_LOG(APP_LOG_LEVEL_INFO, "In Raw Data Handler, samples = %u, time = %lu", (unsigned int)num_samples, (long unsigned int)timestamp);
  APP_LOG(APP_LOG_LEVEL_INFO, "X = %d, Y = %d, and Z = %d", data->x, data->y, data->z);
}

static void window_load(Window *window) {
  accel_raw_data_service_subscribe(100, raw_data_handler);
}

static void window_unload(Window *window) {
  
}

static void init(void) {
  s_window = window_create();
  window_set_click_config_provider(s_window, click_config_provider);
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, false);
}

static void deinit(void) {
  window_destroy(s_window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", s_window);

  app_event_loop();
  deinit();
}
