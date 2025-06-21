#include "wifi_settings.h"
#include "../../ui_manager/ui_common.h"
#include "../../ui_manager/page_manager.h"
#include "../../icons/ui_icons.h"
#include "lvgl.h"

static const char *page_title = "WIFI设置";

// style set
static lv_style_t cont_style;
static lv_style_t btn_style;
static lv_style_t label_style;

static void page_style_init(void)
{
    // parent style
    lv_style_init(&cont_style);
    lv_style_set_bg_color(&cont_style, lv_color_black());
    lv_style_set_border_opa(&cont_style, LV_OPA_TRANSP);
    lv_style_set_pad_all(&cont_style, 0);
    lv_style_set_size(&cont_style, LV_PCT(100), LV_PCT(100));
    lv_style_set_pad_top(&cont_style, 5);
    lv_style_set_pad_bottom(&cont_style, 5);
    lv_style_set_pad_left(&cont_style, 10);
    lv_style_set_pad_right(&cont_style, 10);

    // btn style
    lv_style_init(&btn_style);
    lv_style_set_bg_color(&btn_style, lv_color_hex(0x60e5e5));
    lv_style_set_bg_opa(&btn_style, LV_OPA_40);

    // label style
    lv_style_init(&label_style);
    lv_style_set_text_font(&label_style, &lv_font_CN_Bold_2);
    lv_style_set_text_color(&label_style, lv_color_hex(0x60e5e5));
}

static void textarea_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    wifi_settings_t *me = lv_event_get_user_data(e);

    if (code == LV_EVENT_READY)
    {
        const char *text = lv_textarea_get_text(ta);
        if (lv_strlen(text) == 0)
        {
            goto exit;
        }

        if (me->input_type == TA_KB_INTPUT_DOMAIN)
        {
            lv_strlcpy(me->domain, text, sizeof(me->domain));
            lv_textarea_set_text(me->domain_ta, text);
            LV_LOG("domain name: %s", text);
        }
        else if (me->input_type == TA_KB_INTPUT_PORT)
        {
            lv_textarea_set_text(me->port_ta, text);
            lv_strlcpy(me->port, text, sizeof(me->port));
            LV_LOG("port: %s", text);
        }
    exit:
        lv_textarea_set_text(ta, "");
        lv_obj_clear_flag(me->wifi_set_cont, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(me->ta_kb_cont, LV_OBJ_FLAG_HIDDEN);
    }
}

static lv_obj_t *textarea_keyboard_init(wifi_settings_t *me, lv_obj_t *parent)
{
    lv_obj_t *ta_kb_cont = lv_obj_create(parent);
    lv_obj_set_style_size(ta_kb_cont, LV_PCT(100), LV_PCT(100), 0);
    lv_obj_set_style_bg_color(ta_kb_cont, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(ta_kb_cont, LV_OPA_COVER, 0);
    lv_obj_set_style_border_opa(ta_kb_cont, LV_OPA_TRANSP, 0);

    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(4), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(ta_kb_cont, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(ta_kb_cont, col_dsc, row_dsc);
    lv_obj_clear_flag(ta_kb_cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_pad_all(ta_kb_cont, 0, 0);
    lv_obj_set_style_pad_column(ta_kb_cont, 0, 0);
    lv_obj_set_style_pad_row(ta_kb_cont, 0, 0);

    lv_obj_t *ta = lv_textarea_create(ta_kb_cont);
    lv_obj_set_grid_cell(ta, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_textarea_set_password_mode(ta, false);
    lv_obj_set_style_text_font(ta, &lv_font_CN_Bold_2, LV_PART_MAIN);
    lv_textarea_set_text(ta, "");
    lv_textarea_set_one_line(ta, true);
    lv_obj_set_style_border_opa(ta, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_text_color(ta, lv_color_black(), LV_PART_MAIN);

    lv_obj_t *kb = lv_keyboard_create(ta_kb_cont);
    lv_obj_set_grid_cell(kb, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_SPECIAL);
    lv_obj_set_style_text_color(kb, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(kb, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_opa(kb, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_color(kb, lv_color_hex(0x0f4c4c), LV_PART_ITEMS | LV_STATE_PRESSED);

    lv_keyboard_set_textarea(kb, ta);
    lv_obj_add_event_cb(ta, textarea_event_cb, LV_EVENT_ALL, me);

    lv_obj_add_flag(ta_kb_cont, LV_OBJ_FLAG_HIDDEN);
    return ta_kb_cont;
}

static void domain_textarea_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    wifi_settings_t *me = lv_event_get_user_data(e);

    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
    {
        LV_LOG("Prepare to insert domain.");
        me->input_type = TA_KB_INTPUT_DOMAIN;
        lv_obj_add_flag(me->wifi_set_cont, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(me->ta_kb_cont, LV_OBJ_FLAG_HIDDEN);
    }
}

static void port_textarea_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    wifi_settings_t *me = lv_event_get_user_data(e);

    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
    {
        LV_LOG("Prepare to insert port.");
        me->input_type = TA_KB_INTPUT_PORT;
        lv_obj_add_flag(me->wifi_set_cont, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(me->ta_kb_cont, LV_OBJ_FLAG_HIDDEN);
    }
}
static void intput_network_info(wifi_settings_t *me, lv_obj_t *parent)
{
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(4), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(parent, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(parent, col_dsc, row_dsc);
    lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_pad_all(parent, 0, 0);
    lv_obj_set_style_pad_column(parent, 0, 0);
    lv_obj_set_style_pad_row(parent, 0, 0);

    lv_obj_t *domain_name = lv_label_create(parent);
    lv_obj_set_grid_cell(domain_name, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_style_text_color(domain_name, lv_color_white(), 0);
    lv_obj_set_style_text_font(domain_name, &lv_font_CN_Bold_2, 0);
    lv_label_set_text(domain_name, "域名:");

    lv_obj_t *domain_ta = lv_textarea_create(parent);
    lv_obj_set_grid_cell(domain_ta, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_style_text_font(domain_ta, &lv_font_CN_Bold_2, 0);
    lv_obj_set_style_bg_color(domain_ta, lv_color_black(), 0);
    lv_obj_set_style_text_color(domain_ta, lv_color_white(), 0);
    lv_textarea_set_text(domain_ta, "www.cubic.com");
    lv_textarea_set_one_line(domain_ta, true);
    lv_obj_add_event_cb(domain_ta, domain_textarea_event_cb, LV_EVENT_ALL, me);

    lv_obj_t *port_name = lv_label_create(parent);
    lv_obj_set_grid_cell(port_name, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_style_text_color(port_name, lv_color_white(), 0);
    lv_obj_set_style_text_font(port_name, &lv_font_CN_Bold_2, 0);
    lv_label_set_text(port_name, "端口:");

    lv_obj_t *port_ta = lv_textarea_create(parent);
    lv_obj_set_grid_cell(port_ta, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_style_text_font(port_ta, &lv_font_CN_Bold_2, 0);
    lv_obj_set_style_text_color(port_ta, lv_color_white(), 0);
    lv_obj_set_style_bg_color(port_ta, lv_color_black(), 0);
    lv_textarea_set_text(port_ta, "2223");
    lv_textarea_set_one_line(port_ta, true);
    lv_obj_add_event_cb(port_ta, port_textarea_event_cb, LV_EVENT_ALL, me);

    me->domain_ta = domain_ta;
    me->port_ta = port_ta;
}

static void wifi_info_set(wifi_settings_t *me, lv_obj_t *parent)
{
    static lv_coord_t col_dsc[] = {LV_GRID_FR(4), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(parent, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(parent, col_dsc, row_dsc);
    lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_pad_all(parent, 0, 0);
    lv_obj_set_style_pad_column(parent, 0, 0);
    lv_obj_set_style_pad_row(parent, 0, 0);

    // network information enter parent
    lv_obj_t *wifi_info_cont = lv_obj_create(parent);
    lv_obj_add_style(wifi_info_cont, &cont_style, 0);
    lv_obj_set_grid_cell(wifi_info_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
    intput_network_info(me, wifi_info_cont);

    lv_obj_t *check_btn = lv_btn_create(parent);
    lv_obj_add_style(check_btn, &btn_style, 0);
    lv_obj_set_style_radius(check_btn, 15, LV_PART_MAIN);
    lv_obj_t *check_label = lv_label_create(check_btn);
    lv_obj_add_style(check_label, &label_style, 0);
    lv_label_set_text(check_label, "确认");
    lv_obj_set_grid_cell(check_btn, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
}

static lv_obj_t *main_page_create(wifi_settings_t *me, lv_obj_t *parent)
{
    lv_obj_t *wifi_set_cont = lv_obj_create(parent);
    lv_obj_add_style(wifi_set_cont, &cont_style, 0);

    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(2), LV_GRID_FR(2), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(wifi_set_cont, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(wifi_set_cont, col_dsc, row_dsc);
    lv_obj_clear_flag(wifi_set_cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_pad_all(wifi_set_cont, 0, 0);
    lv_obj_set_style_pad_column(wifi_set_cont, 0, 0);
    lv_obj_set_style_pad_row(wifi_set_cont, 0, 0);

    // title set
    lv_obj_t *title_cont = lv_obj_create(wifi_set_cont);
    lv_obj_set_grid_cell(title_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_add_style(title_cont, &cont_style, 0);
    lv_obj_t *cont_title = lv_label_create(title_cont);
    lv_obj_add_style(cont_title, &label_style, 0);
    lv_label_set_text(cont_title, "网络设置");

    // network information set
    lv_obj_t *info_set_cont = lv_obj_create(wifi_set_cont);
    lv_obj_add_style(info_set_cont, &cont_style, 0);
    lv_obj_set_grid_cell(info_set_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    wifi_info_set(me, info_set_cont);

    // start connect btn set
    lv_obj_t *start_connect_btn = lv_btn_create(wifi_set_cont);
    lv_obj_add_style(start_connect_btn, &btn_style, 0);
    lv_obj_t *start_connect_label = lv_label_create(start_connect_btn);
    lv_obj_set_style_text_color(start_connect_label, lv_obj_get_style_bg_color(start_connect_btn, 0), 0);
    lv_label_set_text(start_connect_label, "开始配网");
    lv_obj_add_style(start_connect_label, &label_style, 0);
    lv_obj_set_grid_cell(start_connect_btn, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 2, 1);

    me->callback_obj[WIFI_PAGE_BTN_START_CONNECT] = start_connect_btn;
    return wifi_set_cont;
}

static void _page_load(void *user_data)
{
    wifi_settings_t *me = (wifi_settings_t *)user_data;
    lv_scr_load(me->screen);
    lv_obj_add_flag(me->ta_kb_cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(me->wifi_set_cont, LV_OBJ_FLAG_HIDDEN);
}

lv_obj_t *wifi_settings_init(wifi_settings_t *me)
{
    page_style_init();
    me->screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(me->screen, 0, 0);
    page_manager_register(PAGE_INDEX_WIFI, me, _page_load);

    me->main_cont = ui_common_settings_page_create(me->screen, page_title);
    me->ta_kb_cont = textarea_keyboard_init(me, me->main_cont);
    me->wifi_set_cont = main_page_create(me, me->main_cont);
    return me->screen;
}
