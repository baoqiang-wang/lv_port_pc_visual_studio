
idf_component_register(SRCS "home.c" "home_cfg.c"
    INCLUDE_DIRS "."
    REQUIRES "lvgl" "environment_cfg" "component_cfg" "settings" "ui_manager" "icons")
