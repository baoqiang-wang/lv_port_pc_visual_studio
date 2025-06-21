#include "home.h"
#include "time.h"
#include <stdio.h>
#include "../ui_manager/page_manager.h"
#include "../ui_manager/ui_common.h"
#include "../icons/ui_icons.h"

static void _multi_cont_element_abs_pos_set(lv_obj_t *obj, int32_t x_abs, int32_t y_abs)
{
	int32_t parent_w = 480;
	int32_t parent_h = 400;

	int32_t x_pct = (int32_t)(x_abs * 100) / parent_w;
	int32_t y_pct = (int32_t)(y_abs * 100) / parent_h;

	lv_obj_set_pos(obj, lv_pct(x_pct), lv_pct(y_pct));
}

static lv_obj_t *_main_ctrl_btn_create(lv_obj_t *parent, const void *icon_dsc, int grid_row, int grid_col, int grid_row_span, int grid_col_span)
{

	static lv_style_t main_ctrl_btn_style;
	lv_style_init(&main_ctrl_btn_style);
	lv_style_set_radius(&main_ctrl_btn_style, LV_RADIUS_CIRCLE);
	lv_style_set_bg_opa(&main_ctrl_btn_style, LV_OPA_TRANSP);

	lv_obj_t *btn = lv_btn_create(parent);
	lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_CENTER, grid_col, grid_col_span,
						 LV_GRID_ALIGN_CENTER, grid_row, grid_row_span);

	lv_obj_add_style(btn, &main_ctrl_btn_style, LV_PART_MAIN);

	lv_obj_t *icon = lv_img_create(btn);
	lv_img_set_src(icon, icon_dsc);
	lv_obj_center(icon);

	return btn;
}

static lv_obj_t *_multi_btn_create(lv_obj_t *parent, const void *icon_dsc, int32_t size, int32_t x_abs, int32_t y_abs)
{
	static lv_style_t multi_btn_style;
	lv_style_init(&multi_btn_style);
	lv_style_set_size(&multi_btn_style, size, size);
	lv_style_set_radius(&multi_btn_style, LV_RADIUS_CIRCLE);
	lv_style_set_bg_color(&multi_btn_style, lv_color_black());
	lv_style_set_bg_opa(&multi_btn_style, LV_OPA_TRANSP);

	lv_obj_t *btn = lv_btn_create(parent);
	lv_obj_add_style(btn, &multi_btn_style, LV_PART_MAIN);
	_multi_cont_element_abs_pos_set(btn, x_abs, y_abs);

	lv_obj_t *icon = lv_img_create(btn);
	lv_img_set_src(icon, icon_dsc);
	lv_obj_set_style_bg_opa(icon, LV_OPA_TRANSP, 0);
	lv_obj_center(icon);

	return btn;
}

static lv_obj_t *_clock_laber_create(lv_obj_t *parent, int32_t x, int32_t y)
{
	lv_obj_t *clock_label = lv_label_create(parent);
	lv_obj_set_pos(clock_label, x, y);
	lv_obj_set_style_text_font(clock_label, &lv_font_CN_Bold_2, LV_STYLE_STATE_CMP_SAME);
	lv_obj_set_style_text_color(clock_label, lv_color_white(), LV_STYLE_STATE_CMP_SAME);
	lv_label_set_text(clock_label, __TIME__);
	return clock_label;
}

static void _controller_element_create(home_t *me, lv_obj_t *parent)
{
	me->cur_temp_label = lv_label_create(parent);
	_multi_cont_element_abs_pos_set(me->cur_temp_label, 180, 170);
	lv_obj_set_style_text_align(me->cur_temp_label, LV_ALIGN_CENTER, 0);
	lv_label_set_long_mode(me->cur_temp_label, LV_LABEL_LONG_DOT);
	lv_obj_set_style_text_font(me->cur_temp_label, &lv_font_CN_Bold_2, 0);
	lv_obj_set_style_text_color(me->cur_temp_label, lv_color_white(), LV_STYLE_STATE_CMP_SAME);

	me->set_temp_label = lv_label_create(parent);
	_multi_cont_element_abs_pos_set(me->set_temp_label, 180, 230);
	lv_obj_set_style_text_align(me->set_temp_label, LV_ALIGN_CENTER, 0);
	lv_label_set_long_mode(me->set_temp_label, LV_LABEL_LONG_DOT);
	lv_obj_set_style_text_font(me->set_temp_label, &lv_font_CN_Bold_2, 0);
	lv_obj_set_style_text_color(me->set_temp_label, lv_color_white(), LV_STYLE_STATE_CMP_SAME);

	me->mode_icon = lv_img_create(parent);
	_multi_cont_element_abs_pos_set(me->mode_icon, 420, 70);
	lv_img_set_src(me->mode_icon, &ventilation_icon);

	// init status
	lv_label_set_text(me->cur_temp_label, "Cur --.--");
	lv_label_set_text(me->set_temp_label, "Set --.--");
}

static lv_obj_t *_arc_create(lv_obj_t *parent)
{
	lv_obj_t *arc = lv_arc_create(parent);
	lv_obj_set_style_size(arc, 300, 300, 0);
	lv_obj_set_style_align(arc, LV_ALIGN_CENTER, 0);

	lv_arc_set_rotation(arc, 180);

	lv_arc_set_bg_angles(arc, 0, 360);
	lv_obj_set_style_arc_color(arc, lv_color_hex(0x808080), LV_PART_MAIN);
	lv_obj_set_style_arc_width(arc, 5, LV_PART_MAIN);

	lv_arc_set_range(arc, 0, 800);

	lv_obj_set_style_arc_color(arc, lv_color_hex(0x00bfbf), LV_PART_INDICATOR);
	lv_obj_set_style_arc_width(arc, 5, LV_PART_INDICATOR);

	lv_obj_set_style_bg_color(arc, lv_color_hex(0x00bfbf), LV_PART_KNOB);
	lv_obj_set_style_pad_all(arc, 8, LV_PART_KNOB);

	lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(arc, LV_OBJ_FLAG_CLICKABLE);

	lv_arc_set_value(arc, 268);

	return arc;
}

static void _mutlti_cont_init(home_t *me)
{
	lv_obj_t *multi_cont = lv_obj_create(me->screen);
	lv_obj_set_grid_cell(multi_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
	lv_obj_set_style_bg_opa(multi_cont, LV_OPA_TRANSP, 0);
	lv_obj_set_style_border_opa(multi_cont, LV_OPA_TRANSP, 0);
	lv_obj_clear_flag(multi_cont, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_t *arc = _arc_create(multi_cont);

	uint32_t btn_size = 30;
	// mode switching button
	lv_obj_t *mode_switching_btn = _multi_btn_create(multi_cont, LV_SYMBOL_HOME, btn_size, 445, 0);

	// cooling and heating button
	lv_obj_t *cooling_btn = _multi_btn_create(multi_cont, &decrease_icon, btn_size, 70, 215);
	lv_obj_t *heating_btn = _multi_btn_create(multi_cont, &increase_icon, btn_size, 385, 215);

	// fan speed button
	lv_obj_t *low_speed_btn = _multi_btn_create(multi_cont, &fan_low_icon, btn_size, 105, 290);
	lv_obj_t *mid_speed_btn = _multi_btn_create(multi_cont, &fan_mid_icon, btn_size, 185, 335);
	lv_obj_t *high_speed_btn = _multi_btn_create(multi_cont, &fan_high_icon, btn_size, 285, 335);
	lv_obj_t *auto_speed_btn = _multi_btn_create(multi_cont, &fan_auto_icon, btn_size, 350, 290);

	me->callback_obj[HOME_PAGE_ARC_CHANGE] = arc;
	me->callback_obj[HOME_PAGE_BTN_MODE_SWITCHING] = mode_switching_btn;
	me->callback_obj[HOME_PAGE_BTN_AUTO_SPEED] = auto_speed_btn;
	me->callback_obj[HOME_PAGE_BTN_COOLING] = cooling_btn;
	me->callback_obj[HOME_PAGE_BTN_HEATING] = heating_btn;
	me->callback_obj[HOME_PAGE_BTN_LOW_SPEED] = low_speed_btn;
	me->callback_obj[HOME_PAGE_BTN_MID_SPEED] = mid_speed_btn;
	me->callback_obj[HOME_PAGE_BTN_HIGH_SPEED] = high_speed_btn;

	// clock label set
	me->clock_label = _clock_laber_create(multi_cont, 0, 0);

	// controller element set
	_controller_element_create(me, multi_cont);

	// wifi icon set
	me->wifi_icon = lv_img_create(multi_cont);
	_multi_cont_element_abs_pos_set(me->wifi_icon, 120, 0);
	lv_img_set_src(me->wifi_icon, &wifi_disconnect_icon);
}

static void _main_ctrl_cont_init(home_t *me)
{
	lv_obj_t *main_ctrl_cont = lv_obj_create(me->screen);
	lv_obj_set_grid_cell(main_ctrl_cont, LV_GRID_ALIGN_STRETCH, 0, 1,
						 LV_GRID_ALIGN_STRETCH, 1, 1);
	lv_obj_set_style_bg_opa(main_ctrl_cont, LV_OPA_TRANSP, 0);
	lv_obj_set_style_border_color(main_ctrl_cont, lv_color_hex(0xff0000), 0);
	lv_obj_set_style_border_opa(main_ctrl_cont, LV_OPA_TRANSP, 0);

	static lv_coord_t ctrl_col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
	static lv_coord_t ctrl_row_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
	lv_obj_set_layout(main_ctrl_cont, LV_LAYOUT_GRID);
	lv_obj_set_grid_dsc_array(main_ctrl_cont, ctrl_col_dsc, ctrl_row_dsc);
	lv_obj_clear_flag(main_ctrl_cont, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_t *settings_btn = _main_ctrl_btn_create(main_ctrl_cont, &settings_icon, 0, 0, 1, 1);
	lv_obj_t *power_btn = _main_ctrl_btn_create(main_ctrl_cont, &power_icon, 0, 1, 1, 1);
	lv_obj_t *comfort_mode_btn = _main_ctrl_btn_create(main_ctrl_cont, &comfort_icon, 0, 2, 1, 1);
	lv_obj_t *eco_mode_btn = _main_ctrl_btn_create(main_ctrl_cont, &eco_icon, 0, 3, 1, 1);

	me->callback_obj[HOME_PAGE_BTN_PWR] = power_btn;
	me->callback_obj[HOME_PAGE_BTN_SETTINGS] = settings_btn;
	me->callback_obj[HOME_PAGE_BTN_COMFORT_MODE] = comfort_mode_btn;
	me->callback_obj[HOME_PAGE_BTN_ECO_MODE] = eco_mode_btn;
}

static void _update_tmr_cb(lv_timer_t *tmr)
{
	home_t *me = lv_timer_get_user_data(tmr);
	if (me->update_tmr_cb)
	{
		me->update_tmr_cb(tmr);
	}
	else
	{
		LV_LOG("update tmr cb is NULL");
	}
}

static void _update_tmr_init(home_t *me)
{
	me->update_tmr = lv_timer_create(_update_tmr_cb, 1000, me);
}

static void _home_page_load(void *user_data)
{
	home_t *me = (home_t *)user_data;
	lv_scr_load(me->screen);
}

static void _main_screen_init(home_t *me)
{
	me->screen = lv_obj_create(NULL);
	page_manager_register(PAGE_INDEX_HOME, me, _home_page_load);
	lv_obj_set_size(me->screen, LV_PCT(100), LV_PCT(100));

	lv_obj_set_style_bg_color(me->screen, lv_color_black(), LV_PART_MAIN);

	static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
	static lv_coord_t row_dsc[] = {LV_GRID_FR(5), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

	lv_obj_set_layout(me->screen, LV_LAYOUT_GRID);
	lv_obj_set_grid_dsc_array(me->screen, col_dsc, row_dsc);

	lv_obj_set_style_pad_all(me->screen, 0, 0);
	lv_obj_set_style_pad_column(me->screen, 0, 0);
	lv_obj_set_style_pad_row(me->screen, 0, 0);
}

void home_page_init(home_t *me)
{
	_main_screen_init(me);
	_main_ctrl_cont_init(me);
	_mutlti_cont_init(me);
	_update_tmr_init(me);
}

void home_page_tmr_cb_register(home_t *me, void (*cb)(lv_timer_t *tmr))
{
	if (cb != NULL)
	{
		me->update_tmr_cb = cb;
		LV_LOG("home page tmr cb register success");
	}
	else
	{
		LV_LOG("home page tmr cb is NULL");
	}
}
