#ifndef __SETTINGS_H
#define __SETTINGS_H

#include "lvgl.h"
#include "src/libs/qrcode/lv_qrcode.h"

typedef enum
{
    SETTINGS_PAGE_BTN_NETWORK_ENTER,
    SETTINGS_PAGE_BTN_DISPLAY_ENTER,
    SETTINGS_PAGE_BTN_TIME_ENTER,
    SETTINGS_PAGE_BTN_ADVANCED_ENTER,
    SETTINGS_PAGE_BTN_SCENARIO_MODE_ENTER,
    SETTINGS_PAGE_BTN_MACHINE_INFO_ENTER,
    SETTINGS_PAGE_CB_MAX
} settings_page_cb_obj_index_t;

typedef struct settings_page
{
    // Main screen
    lv_obj_t *screen;
    // Grid layout
    lv_obj_t *main_cont;


    lv_obj_t *callback_obj[SETTINGS_PAGE_CB_MAX];

} settings_t;

lv_obj_t *settings_page_init(settings_t *me);

#endif