#ifndef __TIME_SETTINGS_H
#define __TIME_SETTINGS_H

#include "lvgl.h"

typedef enum
{
    CLOCK_12_HOUR,
    CLOCK_24_HOUR,
} time_system_t;

typedef enum
{
    AM,
    PM,
} time_period_t;

typedef struct
{
    uint16_t year;
    int8_t month; /**< 1..12 */
    int8_t day;   /**< 1..31 */
    int8_t hour;
    int8_t minute;
    time_period_t period;
    time_system_t system;
} date_time_t;

typedef enum
{
    TIME_PAGE_BTN_12_HOUR,
    TIME_PAGE_BTN_24_HOUR,
    TIME_PAGE_BTN_LOCAL_TIME,
    TIME_PAGE_BTN_NTP_SERVER,
    TIME_PAGE_BTN_LOCAL_TIME_ZONE_ENABLE,
    TIME_PAGE_CB_MAX,
} time_page_cb_obj_index_t;

typedef struct
{
    date_time_t *(*get_date_time_by_local)(void);
    date_time_t *(*get_date_time_by_ntp)(void);
} get_time_ops_t;

typedef struct
{
    lv_obj_t *screen;
    lv_obj_t *main_cont;
    lv_obj_t *callback_obj[TIME_PAGE_CB_MAX];
    date_time_t date_time;
    bool is_use_ntp;

    // rollers
    lv_obj_t *year_roller;
    lv_obj_t *month_roller;
    lv_obj_t *day_roller;
    lv_obj_t *hour_roller;
    lv_obj_t *minute_roller;
    lv_obj_t *time_period_roller;
    void (*time_change_cb)(date_time_t *date_time);
    get_time_ops_t get_time_ops;
} time_settings_t;

lv_obj_t *time_settings_init(time_settings_t *me);
void time_settings_date_time_update(time_settings_t *me, date_time_t *date_time);
void time_settings_time_change_cb_register(time_settings_t *me, void (*time_change_cb)(date_time_t *date_time));
void time_settings_get_time_ops_register(time_settings_t *me, get_time_ops_t *get_time_ops);

#endif