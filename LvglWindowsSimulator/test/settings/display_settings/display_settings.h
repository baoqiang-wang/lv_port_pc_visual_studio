#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "lvgl.h"

typedef struct display_setup
{
    lv_obj_t *window;
    
    lv_obj_t *screen_saver_settings_btn;
    lv_obj_t *screen_saver_settings_label;
    lv_obj_t *screen_brightness_btn;
    lv_obj_t *screen_brightness_label;
    

}display_setup_t;

#endif