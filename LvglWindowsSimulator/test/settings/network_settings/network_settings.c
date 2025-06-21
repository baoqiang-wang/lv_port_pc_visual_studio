#include "network_settings.h"
#include "../..//ui_manager/page_manager.h"
#include "lvgl.h"
#include "../../ui_manager/ui_common.h"
#include "../../icons/ui_icons.h"

static const char *page_title = "网络设置";

static void rs485_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG("RS485 button clicked");
        push_page(PAGE_INDEX_RS485);
    }
}

static void wifi_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG("WIFI button clicked");
        push_page(PAGE_INDEX_WIFI);
    }
}

static void _init_btn_custom_style(lv_style_t *style_btn)
{
    lv_style_init(style_btn);

    lv_style_set_bg_color(style_btn, lv_color_hex(0x079328));
    lv_style_set_radius(style_btn, LV_RADIUS_CIRCLE);
    lv_style_set_border_color(style_btn, lv_color_hex(0x079328));
    lv_style_set_border_width(style_btn, 2);
    lv_style_set_shadow_color(style_btn, lv_color_hex(0x079328));
    lv_style_set_shadow_width(style_btn, 5);
    lv_style_set_shadow_offset_y(style_btn, 3);
    lv_style_set_size(style_btn, 130, 130);
}

static lv_obj_t *_network_interface_grid_set(lv_obj_t *page)
{
    lv_obj_t *component_container = lv_obj_create(page);

    lv_obj_set_grid_cell(component_container, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);

    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(component_container, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(component_container, col_dsc, row_dsc);
    lv_obj_clear_flag(component_container, LV_OBJ_FLAG_SCROLLABLE);
    return component_container;
}

static void _network_function_btn_init(lv_obj_t *parent, lv_style_t *style)
{
    lv_obj_t *rs485_btn = lv_button_create(parent);
    lv_obj_add_style(rs485_btn, style, 0);
    lv_obj_set_grid_cell(rs485_btn, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_add_event_cb(rs485_btn, rs485_btn_event_handler, LV_EVENT_ALL, NULL);

    lv_obj_t *rs485_btn_label = lv_label_create(rs485_btn);
    lv_label_set_text(rs485_btn_label, "RS485");
    lv_obj_set_align(rs485_btn_label, LV_ALIGN_CENTER);

    lv_obj_t *wifi_btn = lv_button_create(parent);
    lv_obj_add_style(wifi_btn, style, 0);
    lv_obj_set_grid_cell(wifi_btn, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_add_event_cb(wifi_btn, wifi_btn_event_handler, LV_EVENT_ALL, NULL);

    lv_obj_t *wifi_btn_label = lv_label_create(wifi_btn);
    lv_label_set_text(wifi_btn_label, "WIFI");
    lv_obj_set_align(wifi_btn_label, LV_ALIGN_CENTER);
}

static void main_page_create(network_settings_t *me)
{
    lv_obj_t *rs485_set_btn = lv_btn_create(me->main_cont);
    lv_obj_t *wifi_set_btn = lv_btn_create(me->main_cont);

    lv_obj_set_style_bg_opa(rs485_set_btn, LV_OPA_TRANSP, 0);
    lv_obj_set_style_bg_opa(wifi_set_btn, LV_OPA_TRANSP, 0);

    lv_obj_t *rs485_set_icon = lv_image_create(rs485_set_btn);
    lv_img_set_src(rs485_set_icon, &rs485_icon);

    lv_obj_t *wifi_icon = lv_image_create(wifi_set_btn);
    lv_img_set_src(wifi_icon, &wifi_set_icon);

    lv_obj_t *rs485_set_label = lv_label_create(me->main_cont);
    lv_label_set_text(rs485_set_label, "RS485");
    lv_obj_set_style_text_font(rs485_set_label, &lv_font_CN_Bold_2, 0);
    lv_obj_set_style_text_color(rs485_set_label, lv_color_hex(0xffffff), 0);

    lv_obj_t *wifi_set_label = lv_label_create(me->main_cont);
    lv_label_set_text(wifi_set_label, "WIFI设置");
    lv_obj_set_style_text_font(wifi_set_label, &lv_font_CN_Bold_2, 0);
    lv_obj_set_style_text_color(wifi_set_label, lv_color_hex(0xffffff), 0);

    lv_obj_align(rs485_set_btn, LV_ALIGN_CENTER, -100, 0);
    lv_obj_align_to(rs485_set_label, rs485_set_btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
    lv_obj_align(wifi_set_btn, LV_ALIGN_CENTER, 100, 0);
    lv_obj_align_to(wifi_set_label, wifi_set_btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);

    me->callback_obj[NETWORK_PAGE_BTN_485_ENTER] = rs485_set_btn;
    me->callback_obj[NETWORK_PAGE_BTN_WIFI_ENTER] = wifi_set_btn;
}

static void network_page_load(void *user_data)
{
    network_settings_t *me = (network_settings_t *)user_data;
    lv_scr_load(me->screen);
}

lv_obj_t *network_page_init(network_settings_t *me)
{
    me->screen = lv_obj_create(NULL);
    page_manager_register(PAGE_INDEX_NETWORK, me, network_page_load);
    lv_obj_set_style_bg_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(me->screen, 0, 0);

    me->main_cont = ui_common_settings_page_create(me->screen, page_title);

    main_page_create(me);
    return me->screen;
}
