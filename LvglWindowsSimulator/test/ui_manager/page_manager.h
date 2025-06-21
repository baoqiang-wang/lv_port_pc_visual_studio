#ifndef __PAGE_MANAGER_H
#define __PAGE_MANAGER_H

#include "lvgl.h"

#define PAGE_TITLE_MAX_LEN 64

typedef enum
{
    PAGE_INDEX_HOME,
    PAGE_INDEX_SETTINGS,
    PAGE_INDEX_NETWORK,
    PAGE_INDEX_RS485,
    PAGE_INDEX_WIFI,
    PAGE_INDEX_DISPLAY,
    PAGE_INDEX_TIME,
    PAGE_INDEX_SCENARIO,
    PAGE_INDEX_ADVANCED,
    PAGE_INDEX_MACHINE_INFO,
    PAGE_INDEX_MAX,
} page_index_t;

typedef struct
{
    void *user_data;
    void (*load)(void *user_data);
} page_manager_t;

void push_page(page_index_t index);
void pop_page(void);
page_index_t current_page(void);
void page_manager_register(page_index_t index, void *user_data, void (*load)(void *user_data));

#endif