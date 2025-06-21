#include "machine_info.h"
#include "../../ui_manager/ui_common.h"
#include "../../ui_manager/page_manager.h"
#include "../../icons/ui_icons.h"

static const char *page_title = "关于本机";
static lv_style_t label_style;

static void page_style_init(void)
{
    lv_style_init(&label_style);
    lv_style_set_bg_opa(&label_style, LV_OPA_TRANSP);
    lv_style_set_text_color(&label_style, lv_color_white());
    lv_style_set_text_font(&label_style, &lv_font_CN_Bold_2);
}

static void machine_info_cont_init(machine_info_t *me)
{
    lv_obj_t *info_cont = lv_obj_create(me->main_cont);
    lv_obj_set_size(info_cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(info_cont, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(info_cont, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_opa(info_cont, LV_OPA_TRANSP, LV_PART_MAIN);

    // child cont
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(info_cont, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(info_cont, col_dsc, row_dsc);
    lv_obj_clear_flag(info_cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *software_version_label = lv_label_create(info_cont);
    lv_obj_add_style(software_version_label, &label_style, LV_PART_MAIN);
    lv_label_set_text(software_version_label, "软件版本: 2.3");
    lv_obj_set_grid_cell(software_version_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    lv_obj_t *hardware_version_label = lv_label_create(info_cont);
    lv_obj_add_style(hardware_version_label, &label_style, LV_PART_MAIN);
    lv_label_set_text(hardware_version_label, "硬件版本: 1.0");
    lv_obj_set_grid_cell(hardware_version_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);

    lv_obj_t *mac_address_label = lv_label_create(info_cont);
    lv_obj_add_style(mac_address_label, &label_style, LV_PART_MAIN);
    lv_label_set_text(mac_address_label, "MAC地址: 845FADSFJA111");
    lv_obj_set_grid_cell(mac_address_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 2, 1);

    lv_obj_t *product_type_label = lv_label_create(info_cont);
    lv_obj_add_style(product_type_label, &label_style, LV_PART_MAIN);
    lv_label_set_text(product_type_label, "产品型号: CUBIC2025061888");
    lv_obj_set_grid_cell(product_type_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 3, 1);

    me->software_version_label = software_version_label;
    me->hardware_version_label = hardware_version_label;
    me->mac_address_label = mac_address_label;
    me->product_type_label = product_type_label;

    // information img set
    lv_obj_t *is_latest_software_version_img = lv_img_create(me->main_cont);
    lv_img_set_src(is_latest_software_version_img, &is_latest_version_icon);
    lv_obj_align(is_latest_software_version_img, LV_ALIGN_TOP_RIGHT, -20, 20);

    lv_obj_t *server_info_img = lv_img_create(me->main_cont);
    lv_img_set_src(server_info_img, &server_icon);
    lv_obj_align(server_info_img, LV_ALIGN_BOTTOM_RIGHT, -5, -20);

    me->is_latest_software_version_img = is_latest_software_version_img;
    me->server_info_img = server_info_img;
}

static void _page_load(void *user_data)
{
    machine_info_t *me = (machine_info_t *)user_data;
    lv_scr_load(me->screen);
}

lv_obj_t *machine_info_init(machine_info_t *me)
{
    page_style_init();
    me->screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(me->screen, 0, 0);
    page_manager_register(PAGE_INDEX_MACHINE_INFO, me, _page_load);

    me->main_cont = ui_common_settings_page_create(me->screen, page_title);
    machine_info_cont_init(me);
    return me->screen;
}

void machine_info_software_version_update(machine_info_t *me, const char *software_version)
{
    lv_label_set_text_fmt(me->software_version_label, "软件版本: %s", software_version);
}

void machine_info_hardware_version_update(machine_info_t *me, const char *hardware_version)
{
    lv_label_set_text_fmt(me->hardware_version_label, "硬件版本: %s", hardware_version);
}
void machine_info_mac_address_update(machine_info_t *me, const char *mac_address)
{
    lv_label_set_text_fmt(me->mac_address_label, "MAC地址: %s", mac_address);
}

void machine_info_product_type_update(machine_info_t *me, const char *product_type)
{
    lv_label_set_text_fmt(me->product_type_label, "产品类型: %s", product_type);
}

void machine_info_is_latest_version_update(machine_info_t *me, bool is_latest_version)
{
    if (is_latest_version)
    {
        lv_img_set_src(me->is_latest_software_version_img, &is_latest_version_icon);
    }
    else
    {
        lv_img_set_src(me->is_latest_software_version_img, &non_latest_version_icon);
    }
}

void machine_info_server_info_img_update(machine_info_t *me, void *img_src)
{
    lv_img_set_src(me->server_info_img, img_src);
}
