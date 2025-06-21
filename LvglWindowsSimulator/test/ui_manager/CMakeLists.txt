idf_component_register(SRCS "page_manager.c" "ui_common.c" "lv_font_CN_Bold_2.c"
  INCLUDE_DIRS "."
  REQUIRES "lvgl" "network_settings" "display_settings" "time_settings" "scenario_settings" "advanced_settings" "machine_info" "icons"
)