#ifndef _ADVANCED_SETTINGS_H
#define _ADVANCED_SETTINGS_H

#include "lvgl.h"
#include "config_item.h"

typedef struct
{
    lv_obj_t *screen;

    // Conts
    lv_obj_t *main_cont;
    lv_obj_t *config_cont;
    lv_obj_t *pwd_cont;

    // btn
    lv_obj_t *callback_obj[CONFIG_SET_MAX];

    // Password
    lv_obj_t *pwd_ta;
    lv_obj_t *pwd_kb;
    lv_obj_t *input_err_prompt;
    char password[6];
} advanced_settings_t;

lv_obj_t *advanced_settings_init(advanced_settings_t *me);

#endif
