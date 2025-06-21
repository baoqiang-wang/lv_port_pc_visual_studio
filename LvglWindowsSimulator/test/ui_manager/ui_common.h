#ifndef __UI_COMMON_H
#define __UI_COMMON_H

#include "lvgl.h"

LV_FONT_DECLARE(lv_font_CN_Bold_2)

lv_obj_t *ui_common_settings_page_create(lv_obj_t *parent, const char *title_text);

void ui_common_event_cb_by_index_register(lv_obj_t **btn_stack, uint16_t index, void (*event_cb)(lv_event_t *e), void *user_data);
#endif