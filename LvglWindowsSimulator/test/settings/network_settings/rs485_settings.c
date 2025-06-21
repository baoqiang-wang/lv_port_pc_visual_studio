#include "rs485_settings.h"
#include "network_settings.h"
#include "../../ui_manager/page_manager.h"
#include "lvgl.h"
#include "../../ui_manager/ui_common.h"
#include "../../icons/ui_icons.h"

static const char *page_title = "RS-485设置";

// style set
static lv_style_t cont_style;
static lv_style_t btn_style;
static lv_style_t label_style;

static void page_style_init(void)
{
    // cont style
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
    lv_style_set_bg_color(&btn_style, lv_color_black());
    lv_style_set_bg_opa(&btn_style, LV_OPA_TRANSP);

    // label style
    lv_style_init(&label_style);
    lv_style_set_text_font(&label_style, &lv_font_CN_Bold_2);
    lv_style_set_text_color(&label_style, lv_color_hex(0xededed));
}

static void set_button_style(lv_obj_t *btn, bool selected)
{
    if (selected)
    {
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x4A90E2), LV_PART_MAIN); // 已选中颜色
        lv_obj_set_style_text_color(btn, lv_color_white(), LV_PART_MAIN);
    }
    else
    {
        lv_obj_set_style_bg_color(btn, lv_color_hex(0xededed), LV_PART_MAIN); // 未选中颜色
        lv_obj_set_style_text_color(btn, lv_color_black(), LV_PART_MAIN);
    }
}

static lv_obj_t *_btn_create(lv_obj_t *parent, const char *btn_name)
{
    lv_obj_t *btn_cont = lv_obj_create(parent);
    lv_obj_set_width(btn_cont, LV_SIZE_CONTENT);
    lv_obj_set_height(btn_cont, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(btn_cont, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(btn_cont, 0, LV_PART_MAIN);
    lv_obj_set_flex_flow(btn_cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(btn_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    lv_obj_set_style_pad_all(btn_cont, 0, 0);
    lv_obj_set_style_pad_left(btn_cont, 0, 0);
    lv_obj_set_style_pad_right(btn_cont, 0, 0);

    lv_obj_t *btn = lv_button_create(btn_cont);
    lv_obj_set_size(btn, 30, 30);
    lv_obj_set_style_radius(btn, 15, LV_PART_MAIN);
    set_button_style(btn, 0);

    lv_obj_t *label = lv_label_create(btn_cont);
    lv_obj_set_style_text_font(label, &lv_font_CN_Bold_2, 0);
    lv_obj_set_style_pad_left(label, 5, LV_PART_MAIN);
    lv_label_set_text(label, btn_name);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);

    return btn;
}

static void _device_addr_cont_init(rs485_settings_t *me, lv_obj_t *parent)
{
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(4), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(parent, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(parent, col_dsc, row_dsc);
    lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_pad_all(parent, 0, 0);
    lv_obj_set_style_pad_column(parent, 0, 0);
    lv_obj_set_style_pad_row(parent, 0, 0);

    lv_obj_t *cont_title = lv_label_create(parent);
    lv_label_set_text(cont_title, "Modbus设备地址");
    lv_obj_add_style(cont_title, &label_style, 0);
    lv_obj_set_grid_cell(cont_title, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    lv_obj_t *child_cont = lv_obj_create(parent);
    lv_obj_add_style(child_cont, &cont_style, 0);
    lv_obj_set_grid_cell(child_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);

    lv_obj_t *addr_decrease_btn = lv_btn_create(child_cont);
    lv_obj_t *addr_increase_btn = lv_btn_create(child_cont);
    lv_obj_t *addr_label = lv_label_create(child_cont);

    lv_obj_add_style(addr_decrease_btn, &btn_style, 0);
    lv_obj_add_style(addr_increase_btn, &btn_style, 0);
    lv_obj_add_style(addr_label, &label_style, 0);

    lv_obj_align(addr_decrease_btn, LV_ALIGN_LEFT_MID, 50, 0);
    lv_obj_align(addr_increase_btn, LV_ALIGN_RIGHT_MID, -50, 0);
    lv_obj_align(addr_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *addr_decrease_icon = lv_image_create(addr_decrease_btn);
    lv_img_set_src(addr_decrease_icon, &decrease_icon);

    lv_obj_t *addr_increase_icon = lv_image_create(addr_increase_btn);
    lv_img_set_src(addr_increase_icon, &increase_icon);

    lv_label_set_text(addr_label, "01");
}

static void _device_parament_cont_init(rs485_settings_t *me, lv_obj_t *parent)
{
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(parent, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(parent, col_dsc, row_dsc);
    lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_pad_all(parent, 0, 0);
    lv_obj_set_style_pad_column(parent, 0, 0);
    lv_obj_set_style_pad_row(parent, 0, 0);

    lv_obj_t *cont_title = lv_label_create(parent);
    lv_label_set_text(cont_title, "Modbus通讯参数");
    lv_obj_add_style(cont_title, &label_style, 0);
    lv_obj_set_grid_cell(cont_title, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    // Baudrate cont set
    lv_obj_t *baudrate_cont = lv_obj_create(parent);
    lv_obj_add_style(baudrate_cont, &cont_style, 0);
    lv_obj_set_flex_flow(baudrate_cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_grid_cell(baudrate_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);

    me->callback_obj[RS485_PAGE_BTN_485_BAUD_RATE_4800] = _btn_create(baudrate_cont, "4800");
    me->callback_obj[RS485_PAGE_BTN_485_BAUD_RATE_9600] = _btn_create(baudrate_cont, "9600");

    // Parity cont set
    lv_obj_t *parity_cont = lv_obj_create(parent);
    lv_obj_add_style(parity_cont, &cont_style, 0);
    lv_obj_set_flex_flow(parity_cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_grid_cell(parity_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 2, 1);

    me->callback_obj[RS485_PAGE_BTN_485_ODD_PARITY] = _btn_create(parity_cont, "奇校验");
    me->callback_obj[RS485_PAGE_BTN_485_EVEN_PARITY] = _btn_create(parity_cont, "偶校验");
    me->callback_obj[RS485_PAGE_BTN_485_NO_PARITY] = _btn_create(parity_cont, "无校验");
}

static void main_page_create(rs485_settings_t *me)
{
    lv_obj_t *cont = lv_obj_create(me->main_cont);
    lv_obj_add_style(cont, &cont_style, 0);

    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(cont, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_pad_all(cont, 0, 0);
    lv_obj_set_style_pad_column(cont, 0, 0);
    lv_obj_set_style_pad_row(cont, 0, 0);

    lv_obj_t *device_addr_cont = lv_obj_create(cont);
    lv_obj_add_style(device_addr_cont, &cont_style, 0);
    lv_obj_set_grid_cell(device_addr_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

    lv_obj_t *device_parament_cont = lv_obj_create(cont);
    lv_obj_add_style(device_parament_cont, &cont_style, 0);
    lv_obj_set_grid_cell(device_parament_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);

    _device_addr_cont_init(me, device_addr_cont);
    _device_parament_cont_init(me, device_parament_cont);
}

static void rs485_page_load(void *user_data)
{
    rs485_settings_t *me = (rs485_settings_t *)user_data;
    lv_scr_load(me->screen);
}

lv_obj_t *rs485_settings_init(rs485_settings_t *me)
{
    page_style_init();
    me->screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(me->screen, 0, 0);
    page_manager_register(PAGE_INDEX_RS485, me, rs485_page_load);

    me->main_cont = ui_common_settings_page_create(me->screen, page_title);
    main_page_create(me);
    return me->screen;
}
