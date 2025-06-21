idf_component_register(SRCS "settings_cfg.c"
  INCLUDE_DIRS "."
  REQUIRES "lvgl" "ui_manager" "main_settings" "network_settings" "display_settings" "time_settings" "scenario_settings" "advanced_settings" "machine_info"
)
