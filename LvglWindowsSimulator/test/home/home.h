#ifndef __HOME_H
#define __HOME_H

#include "lvgl.h"

typedef enum
{
    HOME_PAGE_BTN_PWR,
    HOME_PAGE_BTN_SETTINGS,
    HOME_PAGE_BTN_COMFORT_MODE,
    HOME_PAGE_BTN_ECO_MODE,
    HOME_PAGE_BTN_MODE_SWITCHING,
    HOME_PAGE_BTN_COOLING,
    HOME_PAGE_BTN_HEATING,
    HOME_PAGE_BTN_LOW_SPEED,
    HOME_PAGE_BTN_MID_SPEED,
    HOME_PAGE_BTN_HIGH_SPEED,
    HOME_PAGE_BTN_AUTO_SPEED,
    HOME_PAGE_BTN_SLIDING_DAMPER,
    HOME_PAGE_ARC_CHANGE,
    HOME_PAGE_CB_MAX,
} home_page_cb_obj_index_t;

typedef struct
{
    lv_obj_t *screen;

    lv_obj_t *clock_label;
    lv_obj_t *cur_temp_label;
    lv_obj_t *set_temp_label;
    lv_obj_t *wifi_icon;
    lv_obj_t *mode_icon;

    lv_obj_t *callback_obj[HOME_PAGE_CB_MAX];

    // Timer
    lv_timer_t *update_tmr;
    void (*update_tmr_cb)(lv_timer_t *tmr);
    void *user_data;
} home_t;

void home_page_init(home_t *me);
void home_page_tmr_cb_register(home_t *me, void (*cb)(lv_timer_t *tmr));

#endif
