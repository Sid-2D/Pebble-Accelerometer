#include <pebble.h>
#include <stdio.h>

static Window *s_window;
static TextLayer *s_text_layer;
static char accel_values[60];
// const double SCALE_FACTOR = 0.00980665;

static void click_config_provider(void *context) {

}

static void raw_data_handler(AccelRawData *data, uint32_t num_samples, uint64_t timestamp) {
  APP_LOG(APP_LOG_LEVEL_INFO, "In Raw Data Handler, samples = %u, time = %lu", (unsigned int)num_samples, (long unsigned int)timestamp);
  APP_LOG(APP_LOG_LEVEL_INFO, "X = %d, Y = %d, and Z = %d", data->x, data->y, data->z);
  snprintf(accel_values, sizeof(accel_values), "X = %d\nY = %d\nZ = %d", data->x, data->y, data->z);
  text_layer_set_text(s_text_layer, accel_values);
}

static void window_load(Window *window) {
  accel_raw_data_service_subscribe(25, raw_data_handler);

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_text_layer = text_layer_create(GRect(0, 40, bounds.size.w, 60));
  text_layer_set_text(s_text_layer, "Loading...");
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
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