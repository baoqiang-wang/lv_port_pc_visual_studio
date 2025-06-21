#include "settings.h"
#include "lvgl.h"
#include "../../ui_manager/page_manager.h"
#include "../../ui_manager/ui_common.h"
#include "../../icons/ui_icons.h"

static const char *page_title = "系统设置";

static lv_style_t btn_style;

static void _init_btn_custom_style(lv_style_t *btn_style)
{
    lv_style_init(btn_style);

    lv_style_set_bg_color(btn_style, lv_color_black());
    lv_style_set_radius(btn_style, LV_RADIUS_CIRCLE);
    lv_style_set_border_color(btn_style, lv_color_black());
    lv_style_set_border_width(btn_style, 2);
    lv_style_set_shadow_color(btn_style, lv_color_black());
    lv_style_set_shadow_width(btn_style, 5);
    lv_style_set_shadow_offset_y(btn_style, 3);
    lv_style_set_size(btn_style, 50, 50);
}

static void _main_cont_grid_set(settings_t *me)
{
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(me->main_cont, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(me->main_cont, col_dsc, row_dsc);
    lv_obj_clear_flag(me->main_cont, LV_OBJ_FLAG_SCROLLABLE);
}

static lv_obj_t *_create_button_with_style(lv_style_t *style, lv_obj_t *layout, const char *label_str, void *icon_src, int32_t col, int32_t row, int32_t size)
{
    lv_obj_t *cont = lv_obj_create(layout);
    lv_obj_set_grid_cell(cont, LV_GRID_ALIGN_CENTER, col, size, LV_GRID_ALIGN_CENTER, row, size);
    lv_obj_set_style_bg_color(cont, lv_color_black(), 0);
    lv_obj_set_style_border_width(cont, 0, 0);

    // child cont
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(4), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(cont, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *btn = lv_btn_create(cont);
    lv_obj_add_style(btn, style, 0);
    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

    lv_obj_t *icon = lv_img_create(btn);
    lv_img_set_src(icon, icon_src);
    lv_obj_center(icon);

    lv_obj_t *label = lv_label_create(cont);
    lv_label_set_text(label, label_str);
    lv_obj_set_align(label, LV_ALIGN_CENTER);
    lv_obj_set_style_text_font(label, &lv_font_CN_Bold_2, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_set_grid_cell(label, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);

    return btn;
}

static void _component_btn_create(settings_t *me, lv_style_t *style)
{
    const char *labels[] = {
        "网络设置",
        "显示设置",
        "时间设置",
        "情景模式",
        "高级设置",
        "关于本机"};

    lv_obj_t *network_btn = _create_button_with_style(style, me->main_cont, labels[0], &network_icon, 0, 0, 1);
    lv_obj_t *display_btn = _create_button_with_style(style, me->main_cont, labels[1], &display_icon, 1, 0, 1);
    lv_obj_t *time_btn = _create_button_with_style(style, me->main_cont, labels[2], &time_icon, 2, 0, 1);
    lv_obj_t *scenario_mode_btn = _create_button_with_style(style, me->main_cont, labels[3], &scenario_icon, 1, 1, 1);
    lv_obj_t *advanced_setup_btn = _create_button_with_style(style, me->main_cont, labels[4], &settings_icon, 0, 1, 1);
    lv_obj_t *machine_info_btn = _create_button_with_style(style, me->main_cont, labels[5], &about_icon, 2, 1, 1);

    me->callback_obj[SETTINGS_PAGE_BTN_NETWORK_ENTER] = network_btn;
    me->callback_obj[SETTINGS_PAGE_BTN_DISPLAY_ENTER] = display_btn;
    me->callback_obj[SETTINGS_PAGE_BTN_TIME_ENTER] = time_btn;
    me->callback_obj[SETTINGS_PAGE_BTN_SCENARIO_MODE_ENTER] = scenario_mode_btn;
    me->callback_obj[SETTINGS_PAGE_BTN_ADVANCED_ENTER] = advanced_setup_btn;
    me->callback_obj[SETTINGS_PAGE_BTN_MACHINE_INFO_ENTER] = machine_info_btn;
}

void settings_page_load(void *user_data)
{
    settings_t *me = (settings_t *)user_data;
    lv_scr_load(me->screen);
}

lv_obj_t *settings_page_init(settings_t *me)
{
    _init_btn_custom_style(&btn_style);
    me->screen = lv_obj_create(NULL);
    page_manager_register(PAGE_INDEX_SETTINGS, me, settings_page_load);
    lv_obj_set_style_bg_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(me->screen, 0, 0);

    me->main_cont = ui_common_settings_page_create(me->screen, page_title);
    _main_cont_grid_set(me);
    _component_btn_create(me, &btn_style);
    LV_LOG("settings page init");
    return me->screen;
}
