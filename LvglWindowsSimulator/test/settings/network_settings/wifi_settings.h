#ifndef __WIFI_H
#define __WIFI_H
#include "lvgl.h"

typedef enum
{
    WIFI_PAGE_BTN_START_CONNECT,
    WIFI_PAGE_CB_MAX,
} wifi_settings_cb_obj_index_t;

typedef enum
{
    TA_KB_INTPUT_DOMAIN,
    TA_KB_INTPUT_PORT,
} ta_kb_intput_type_t;

typedef struct
{
    lv_obj_t *screen;
    lv_obj_t *main_cont;
    lv_obj_t *wifi_set_cont;
    lv_obj_t *ta_kb_cont;

    lv_obj_t *callback_obj[WIFI_PAGE_CB_MAX];

    // domain and port
    lv_obj_t *domain_ta;
    lv_obj_t *port_ta;

    char domain[32];
    char port[6];
    ta_kb_intput_type_t input_type;

    void *user_data;
} wifi_settings_t;

lv_obj_t *wifi_settings_init(wifi_settings_t *me);

#endif