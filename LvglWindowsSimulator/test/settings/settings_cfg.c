/*
 * @file settings_cfg.c
 * Created on Wed Jun 11 2025
 * @author Baoqiang WANG, wangbaoqiang.1@outlook.com
 * Copyright (c) Wed Jun 11 2025 CUBIC
 */

#include "settings_cfg.h"
#include "../ui_manager/ui_common.h"
#include "../ui_manager/page_manager.h"

settings_t *settings;
advanced_settings_t *advanced_settings;
network_settings_t *network_settings;
rs485_settings_t *rs485_settings;
wifi_settings_t *wifi_settings;
machine_info_t *machine_info;
time_settings_t *time_settings;
scenario_settings_t* scenario_settings;

static settings_t settings_page_ins;
static advanced_settings_t advanced_settings_page_ins;
static network_settings_t network_page_ins;
static rs485_settings_t rs485_settings_ins;
static wifi_settings_t wifi_settings_ins;
static machine_info_t machine_info_ins;
static time_settings_t time_settings_ins;
static scenario_settings_t* scenario_settings_ins;

void advanced_settings_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    advanced_settings_t *me = lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG("Advanced settings clicked");
        LV_LOG("Password is %s", me->password);
    }
}

// settings page
static void settings_to_network_page(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        push_page(PAGE_INDEX_NETWORK);
    }
}

static void settings_to_display_page(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        push_page(PAGE_INDEX_DISPLAY);
    }
}

static void settings_to_time_page(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        push_page(PAGE_INDEX_TIME);
    }
}

static void settings_to_advanced_page(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        push_page(PAGE_INDEX_ADVANCED);
    }
}
static void settings_to_scenario_page(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        push_page(PAGE_INDEX_SCENARIO);
    }
}
static void settings_to_machine_page(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        push_page(PAGE_INDEX_MACHINE_INFO);
    }
}

static void settings_page_internal_cb_register(void)
{
    ui_common_event_cb_by_index_register(settings->callback_obj, SETTINGS_PAGE_BTN_NETWORK_ENTER, settings_to_network_page, network_settings);
    // ui_common_event_cb_by_index_register(settings->callback_obj, SETTINGS_PAGE_BTN_DISPLAY_ENTER, settings_to_display_page, display_settings);
    ui_common_event_cb_by_index_register(settings->callback_obj, SETTINGS_PAGE_BTN_TIME_ENTER, settings_to_time_page, time_settings);
    ui_common_event_cb_by_index_register(settings->callback_obj, SETTINGS_PAGE_BTN_ADVANCED_ENTER, settings_to_advanced_page, advanced_settings);
    ui_common_event_cb_by_index_register(settings->callback_obj, SETTINGS_PAGE_BTN_SCENARIO_MODE_ENTER, settings_to_scenario_page, scenario_settings);
    ui_common_event_cb_by_index_register(settings->callback_obj, SETTINGS_PAGE_BTN_MACHINE_INFO_ENTER, settings_to_machine_page, machine_info);
}

// network page
static void network_page_rs485_btn_evnent_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        push_page(PAGE_INDEX_RS485);
    }
}

static void network_page_wifi_btn_evnent_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        push_page(PAGE_INDEX_WIFI);
    }
}

static void network_page_internal_cb_register(void)
{
    ui_common_event_cb_by_index_register(network_settings->callback_obj, NETWORK_PAGE_BTN_485_ENTER, network_page_rs485_btn_evnent_cb, network_settings);
    ui_common_event_cb_by_index_register(network_settings->callback_obj, NETWORK_PAGE_BTN_WIFI_ENTER, network_page_wifi_btn_evnent_cb, network_settings);
}

static void internal_cb_register(void)
{
    settings_page_internal_cb_register();
    network_page_internal_cb_register();
}

void settings_cfg(void)
{
    settings_page_init(&settings_page_ins);
    settings = &settings_page_ins;
    advanced_settings_init(&advanced_settings_page_ins);
    advanced_settings = &advanced_settings_page_ins;
    ui_common_event_cb_by_index_register(advanced_settings->callback_obj, CONFIG_SET_SERVER_SETTINGS_RESET, advanced_settings_btn_event_handler, advanced_settings);
    network_page_init(&network_page_ins);
    network_settings = &network_page_ins;
    rs485_settings_init(&rs485_settings_ins);
    rs485_settings = &rs485_settings_ins;
    wifi_settings_init(&wifi_settings_ins);
    wifi_settings = &wifi_settings_ins;
    machine_info_init(&machine_info_ins);
    machine_info = &machine_info_ins;
    time_settings_init(&time_settings_ins);
    time_settings = &time_settings_ins;
    scenario_settings_init(&scenario_settings_ins);
    scenario_settings = &scenario_settings_ins;

    internal_cb_register();
}
