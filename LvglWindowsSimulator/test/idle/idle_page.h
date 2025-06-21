#ifndef __IDLE_SCR_H
#define __IDLE_SCR_H
#include "lvgl.h"

typedef enum
{
    IDLE_PAGE_BTN_PWR,
    IDLE_PAGE_CB_MAX
} idle_page_cb_obj_index_t;

typedef struct idle_page
{
    lv_obj_t *screen;
    lv_obj_t *callback_obj[IDLE_PAGE_CB_MAX];
} idle_page_t;

void idle_page_init(idle_page_t *me);

#endif
