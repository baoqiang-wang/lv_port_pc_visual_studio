#ifndef __RS485_SETTINGS_H
#define __RS485_SETTINGS_H

#include "lvgl.h"

typedef enum
{
    RS485_PAGE_BTN_485_ADD_DECREASE,
    RS485_PAGE_BTN_485_ADD_INCREASE,
    RS485_PAGE_BTN_485_BAUD_RATE_4800,
    RS485_PAGE_BTN_485_BAUD_RATE_9600,
    RS485_PAGE_BTN_485_ODD_PARITY,
    RS485_PAGE_BTN_485_EVEN_PARITY,
    RS485_PAGE_BTN_485_NO_PARITY,
    RS485_PAGE_CB_MAX,
} rs485_page_cb_obj_index_t;

typedef struct
{
    lv_obj_t *screen;
    lv_obj_t *main_cont;

    lv_obj_t *callback_obj[RS485_PAGE_CB_MAX];

} rs485_settings_t;

lv_obj_t *rs485_settings_init(rs485_settings_t *me);

#endif