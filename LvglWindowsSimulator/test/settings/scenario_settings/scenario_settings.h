#ifndef __SCENARIO_PAGE_H
#define __SCENARIO_PAGE_H

#include "lvgl.h"

typedef struct
{
    lv_obj_t* screen;
    lv_obj_t* main_cont;

}scenario_settings_t;

lv_obj_t* scenario_settings_init(scenario_settings_t* me);

#endif
