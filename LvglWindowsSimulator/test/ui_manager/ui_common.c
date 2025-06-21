#include "../icons/ui_icons.h"
#include "ui_common.h"
#include "page_manager.h"

static void back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        pop_page();
    }
}

void _ui_common_create_title_bar(lv_obj_t *parent, const char *title_text)
{
    lv_obj_t *title_bar = lv_obj_create(parent);
    if (title_bar == NULL)
    {
        LV_LOG("Failed to create title bar");
    }

    lv_obj_set_grid_cell(title_bar, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

    static lv_coord_t col_dsc[] = {LV_GRID_FR(15), LV_GRID_FR(85), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(title_bar, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(title_bar, col_dsc, row_dsc);
    lv_obj_clear_flag(title_bar, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(title_bar, lv_color_black(), 0);
    lv_obj_set_style_border_width(title_bar, 0, 0);
    lv_obj_set_style_pad_all(title_bar, 0, 0);
    lv_obj_set_style_pad_column(title_bar, 0, 0);
    lv_obj_set_style_pad_row(title_bar, 0, 0);

    // btn set
    lv_obj_t *back_btn = lv_button_create(title_bar);
    lv_obj_set_style_bg_opa(back_btn, LV_OPA_TRANSP, 0);
    lv_obj_set_grid_cell(back_btn, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    lv_obj_t *back_btn_label = lv_label_create(back_btn);
    lv_label_set_text(back_btn_label, "上一页");
    lv_obj_set_style_text_color(back_btn_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(back_btn_label, &lv_font_CN_Bold_2, 0);
    lv_obj_set_style_align(back_btn_label, LV_ALIGN_CENTER, 0);

    lv_obj_add_event_cb(back_btn, back_btn_event_handler, LV_EVENT_CLICKED, NULL);

    // title set
    lv_obj_t *title = lv_label_create(title_bar);
    lv_obj_set_style_text_font(title, &lv_font_CN_Bold_2, 0);
    lv_label_set_text(title, title_text);
    lv_obj_set_style_text_color(title, lv_color_white(), 0);
    lv_obj_align_to(title, title_bar, LV_ALIGN_CENTER, 30, 0);

    lv_obj_set_grid_cell(title, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
}

static lv_obj_t *_ui_common_create_cont(lv_obj_t *parent)
{
    lv_obj_t *cont = lv_obj_create(parent);
    if (cont == NULL)
    {
        LV_LOG("Failed to create cont");
        return NULL;
    }

    lv_obj_set_grid_cell(cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    lv_obj_set_style_bg_color(cont, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(cont, 0, LV_PART_MAIN);
    return cont;
}
/**
 * @brief Create a settings page
 *
 * @param last_page The last page
 * @param title_text The title text
 * @return lv_obj_t* The settings page
 */
lv_obj_t *ui_common_settings_page_create(lv_obj_t *parent, const char *title_text)
{
    lv_obj_t *page = lv_obj_create(parent);
    lv_obj_set_style_size(page, LV_PCT(100), LV_PCT(100), 0);
    lv_obj_set_style_bg_color(page, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(page, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(page, 0, 0);

    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(15), LV_GRID_FR(85), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(page, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(page, col_dsc, row_dsc);

    lv_obj_set_style_pad_all(page, 0, 0);
    lv_obj_set_style_pad_column(page, 0, 0);
    lv_obj_set_style_pad_row(page, 0, 0);

    _ui_common_create_title_bar(page, title_text);
    return _ui_common_create_cont(page);
}

void ui_common_event_cb_by_index_register(lv_obj_t **btn_stack, uint16_t index, void (*event_cb)(lv_event_t *e), void *user_data)
{
    lv_obj_t *btn = btn_stack[index];
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_ALL, user_data);
}
