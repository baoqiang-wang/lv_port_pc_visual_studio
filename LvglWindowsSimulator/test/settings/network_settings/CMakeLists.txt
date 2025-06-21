idf_component_register(SRCS "network_settings.c" "rs485_settings.c" "wifi_settings.c"
  INCLUDE_DIRS "."
  REQUIRES "lvgl" "ui_manager"
)
