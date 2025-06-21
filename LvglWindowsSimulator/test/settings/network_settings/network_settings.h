#ifndef __NET_WORK_H
#define __NET_WORK_H

#include "lvgl.h"

typedef enum
{
    NETWORK_PAGE_BTN_485_ENTER,
    NETWORK_PAGE_BTN_WIFI_ENTER,
    NETWORK_PAGE_CB_MAX,
} network_page_cb_obj_index_t;

typedef struct
{
    lv_obj_t *screen;
    lv_obj_t *main_cont;

    lv_obj_t *callback_obj[NETWORK_PAGE_CB_MAX];
} network_settings_t;

lv_obj_t *network_page_init(network_settings_t *me);

#endif