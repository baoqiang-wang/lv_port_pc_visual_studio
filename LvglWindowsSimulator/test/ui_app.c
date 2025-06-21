
#include "ui_app.h"
#include "./home/home.h"
#include "./idle/idle_page.h"
#include "./settings/settings_cfg.h"
#include "./ui_manager/page_manager.h"
#include "./ui_manager/ui_common.h"
#include "./icons/ui_icons.h"
#include "math.h"

// UI class
// idle page
extern idle_page_t *idle_page;
extern void idle_page_cfg(void);

extern home_t *home_page;
extern settings_t *settings;
extern advanced_settings_t *advanced_settings;
extern void home_page_cfg(void);
extern void settings_cfg(void);


static void idle_page_pwr_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *scr = lv_event_get_user_data(e);

	if (code == LV_EVENT_CLICKED)
	{
		if (scr != NULL)
		{
			lv_scr_load(scr);
			LV_LOG("Jump to home page");
		}
		else
		{
			LV_LOG("idle_page_pwr_btn_event_handler: scr is NULL");
		}
	}
}

static void _idle_page_cb_register(void)
{
	ui_common_event_cb_by_index_register(idle_page->callback_obj, IDLE_PAGE_BTN_PWR, idle_page_pwr_btn_event_handler, home_page->screen);
}

static void home_page_pwr_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *scr = lv_event_get_user_data(e);

	if (code == LV_EVENT_CLICKED)
	{
			lv_scr_load(scr);
			LV_LOG("Jump to idle page");
	}
}

static void home_page_settings_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		push_page(PAGE_INDEX_SETTINGS);
		LV_LOG("Jump to settings page");
	}
}

static void home_page_arc_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *arc = lv_event_get_target(e);
	home_t *me = lv_event_get_user_data(e);

	if (code == LV_EVENT_VALUE_CHANGED)
	{
		int32_t v = lv_arc_get_value(arc);
		v = LV_CLAMP(0, v, 400);
		if (v != lv_arc_get_value(arc))
		{
			lv_arc_set_value(arc, v);
		}
		lv_label_set_text_fmt(me->set_temp_label, "Set %0.1f°C", (float)v / 10.0f);
	}
}

static void home_page_mode_switch_btn_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	home_t *me = lv_event_get_user_data(e);

	if (code == LV_EVENT_CLICKED)
	{
			LV_LOG("mode switching button clicked");
	}
}

static void _home_page_cb_register(void)
{
	ui_common_event_cb_by_index_register(home_page->callback_obj, HOME_PAGE_BTN_MODE_SWITCHING, home_page_mode_switch_btn_event_cb, home_page);
	ui_common_event_cb_by_index_register(home_page->callback_obj, HOME_PAGE_BTN_PWR, home_page_pwr_btn_event_handler, idle_page->screen);
	ui_common_event_cb_by_index_register(home_page->callback_obj, HOME_PAGE_BTN_SETTINGS, home_page_settings_btn_event_handler, NULL);
	ui_common_event_cb_by_index_register(home_page->callback_obj, HOME_PAGE_ARC_CHANGE, home_page_arc_event_cb, home_page);
}

static void _settings_page_cb_register(void)
{
}

void ui_callback_register(void)
{
	_idle_page_cb_register();
	_home_page_cb_register();
	_settings_page_cb_register();
}

void ui_commponent_cfg(void)
{
	idle_page_cfg();
	home_page_cfg();
	settings_cfg();
	ui_callback_register();

	lv_scr_load(home_page->screen);
}
