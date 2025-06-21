#include "time_settings.h"
#include "../../ui_manager/page_manager.h"
#include "../../ui_manager/ui_common.h"
#include "../../icons/ui_icons.h"
#include <string.h>
#include <stdio.h>

static const char *page_title = "时间和编程";

int is_date_time_equal(date_time_t *a, date_time_t *b)
{
    return (a->year == b->year &&
            a->month == b->month &&
            a->day == b->day &&
            a->hour == b->hour &&
            a->minute == b->minute &&
            a->system == b->system &&
            a->period == b->period);
}

// style set
static lv_style_t cont_style;
static lv_style_t btn_style;
static lv_style_t label_style;

// roller options
static char year_options[400];
static char month_options[50];
static char day_options_big_months[100];
static char day_options_small_months[100];
static char day_options_february_common_year[100];
static char day_options_february_leap_year[100];
static char hour_options_12[50];
static char hour_options_24[200];
static char minute_options[200];
static char second_options[200];
static char *time_system_options;
#define ROLLER_YEAR_START 2020
#define ROLLER_YEAR_END 2079

static void _roller_opts_generate(char *options, int start, int end, int step)
{
    for (int i = start; i <= end; i += step)
    {
        char tmp[16];
        snprintf(tmp, sizeof(tmp), "%d", i);
        strcat(options, tmp);
        if (i < end)
            strcat(options, "\n");
    }
}

static void roller_options_init(void)
{
    time_system_options = "AM\nPM";
    year_options[0] = '\0';
    month_options[0] = '\0';
    day_options_big_months[0] = '\0';
    day_options_small_months[0] = '\0';
    day_options_february_common_year[0] = '\0';
    day_options_february_leap_year[0] = '\0';
    hour_options_12[0] = '\0';
    hour_options_24[0] = '\0';
    minute_options[0] = '\0';
    second_options[0] = '\0';

    _roller_opts_generate(year_options, ROLLER_YEAR_START, ROLLER_YEAR_END, 1);
    _roller_opts_generate(month_options, 1, 12, 1);
    _roller_opts_generate(day_options_big_months, 1, 31, 1);
    _roller_opts_generate(day_options_small_months, 1, 30, 1);
    _roller_opts_generate(day_options_february_common_year, 1, 28, 1);
    _roller_opts_generate(day_options_february_leap_year, 1, 29, 1);
    _roller_opts_generate(hour_options_12, 0, 11, 1);
    _roller_opts_generate(hour_options_24, 0, 23, 1);
    _roller_opts_generate(minute_options, 0, 59, 1);
    _roller_opts_generate(second_options, 0, 59, 1);
}

int isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return 1;
    }
    return 0;
}

char *getMonthDays_opts(int year, int month)
{
    if (month < 1 || month > 12)
    {
        return NULL;
    }

    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return day_options_big_months;
    case 4:
    case 6:
    case 9:
    case 11:
        return day_options_small_months;
    case 2:
        return isLeapYear(year) ? day_options_february_leap_year : day_options_february_common_year;
    default:
        return NULL;
    }
}

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
    lv_style_set_size(&btn_style, 30, 30);
    lv_style_set_radius(&btn_style, 15);
    lv_style_set_bg_color(&btn_style, lv_color_hex(0xededed));

    // label style
    lv_style_init(&label_style);
    lv_style_set_text_font(&label_style, &lv_font_CN_Bold_2);
    lv_style_set_text_color(&label_style, lv_color_hex(0xededed));
}

static void _btn_12_hour_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    time_settings_t *me = lv_event_get_user_data(e);

    if (code == LV_EVENT_CLICKED)
    {
        me->date_time.system = CLOCK_12_HOUR;
        lv_roller_set_options(me->hour_roller, hour_options_12, LV_ROLLER_MODE_NORMAL);
        lv_obj_clear_flag(me->time_period_roller, LV_OBJ_FLAG_HIDDEN);
    }
}

static void _btn_24_hour_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    time_settings_t *me = lv_event_get_user_data(e);

    if (code == LV_EVENT_CLICKED)
    {
        me->date_time.system = CLOCK_24_HOUR;
        lv_roller_set_options(me->hour_roller, hour_options_24, LV_ROLLER_MODE_NORMAL);
        lv_obj_add_flag(me->time_period_roller, LV_OBJ_FLAG_HIDDEN);
    }
}

static void _btn_local_time_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    time_settings_t *me = lv_event_get_user_data(e);

    if (code == LV_EVENT_CLICKED)
    {
        me->date_time.system = CLOCK_12_HOUR;
    }
}

static void _btn_ntp_server_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    time_settings_t *me = lv_event_get_user_data(e);

    if (code == LV_EVENT_CLICKED)
    {
        me->date_time.system = CLOCK_12_HOUR;
    }
}

static void _btn_local_time_zone_enable_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    time_settings_t *me = lv_event_get_user_data(e);

    if (code == LV_EVENT_CLICKED)
    {
        me->date_time.system = CLOCK_12_HOUR;
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
    lv_obj_add_style(btn, &btn_style, 0);

    lv_obj_t *label = lv_label_create(btn_cont);
    lv_obj_set_style_text_font(label, &lv_font_CN_Bold_2, 0);
    lv_obj_set_style_pad_left(label, 5, LV_PART_MAIN);
    lv_label_set_text(label, btn_name);
    lv_obj_add_style(label, &label_style, 0);

    return btn;
}

static void time_system_select_init(time_settings_t *me, lv_obj_t *parent)
{
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(parent, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    me->callback_obj[TIME_PAGE_BTN_12_HOUR] = _btn_create(parent, "12小时制");
    me->callback_obj[TIME_PAGE_BTN_24_HOUR] = _btn_create(parent, "24小时制");
    ui_common_event_cb_by_index_register(me->callback_obj, TIME_PAGE_BTN_12_HOUR, _btn_12_hour_event_handler, me);
    ui_common_event_cb_by_index_register(me->callback_obj, TIME_PAGE_BTN_24_HOUR, _btn_24_hour_event_handler, me);
}

static void time_get_method_select_init(time_settings_t *me, lv_obj_t *parent)
{
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(parent, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    me->callback_obj[TIME_PAGE_BTN_LOCAL_TIME] = _btn_create(parent, "本地设置");
    me->callback_obj[TIME_PAGE_BTN_NTP_SERVER] = _btn_create(parent, "网络获取");
}

static lv_obj_t *local_time_zone_roller_create(time_settings_t *me, lv_obj_t *parent, const char *options, uint8_t grid_x, uint8_t grid_y, void (*event_handler)(lv_event_t *e))
{
    lv_obj_t *roller = lv_roller_create(parent);
    lv_roller_set_options(roller, options, LV_ROLLER_MODE_NORMAL);
    lv_roller_set_visible_row_count(roller, 2);
    lv_roller_set_selected(roller, 2, LV_ANIM_OFF);
    lv_obj_set_style_text_color(roller, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(roller, LV_OPA_TRANSP, LV_PART_SELECTED);
    lv_obj_set_style_bg_opa(roller, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_opa(roller, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_add_event_cb(roller, event_handler, LV_EVENT_ALL, me);
    lv_obj_set_grid_cell(roller, LV_GRID_ALIGN_CENTER, grid_x, 1, LV_GRID_ALIGN_STRETCH, grid_y, 1);
    return roller;
}

static void local_time_zone_label_creat(lv_obj_t *parent, const char *text, uint8_t grid_x, uint8_t grid_y)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_add_style(label, &label_style, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x008B8B), 0);
    lv_label_set_text(label, text);
    lv_obj_set_grid_cell(label, LV_GRID_ALIGN_CENTER, grid_x, 1, LV_GRID_ALIGN_CENTER, grid_y, 1);
}

static inline void time_change_cb(time_settings_t *me)
{
    if (me->time_change_cb)
    {
        me->time_change_cb(&me->date_time);
    }
}

static void year_roller_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target_obj(e);
    time_settings_t *me = (time_settings_t *)lv_event_get_user_data(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected value: %s", buf);

        uint16_t year = atoi(buf);
        me->date_time.year = year;
        lv_roller_set_options(me->day_roller, getMonthDays_opts(me->date_time.year, me->date_time.month), LV_ROLLER_MODE_NORMAL);
        time_change_cb(me);
    }
}

static void month_roller_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target_obj(e);
    time_settings_t *me = (time_settings_t *)lv_event_get_user_data(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected value: %s", buf);

        uint8_t month = atoi(buf);
        me->date_time.month = month;
        lv_roller_set_options(me->day_roller, getMonthDays_opts(me->date_time.year, me->date_time.month), LV_ROLLER_MODE_NORMAL);
        time_change_cb(me);
    }
}

static void day_roller_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target_obj(e);
    time_settings_t *me = (time_settings_t *)lv_event_get_user_data(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected value: %s", buf);

        uint8_t day = atoi(buf);
        me->date_time.day = day;
        time_change_cb(me);
    }
}

static void hour_roller_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target_obj(e);
    time_settings_t *me = (time_settings_t *)lv_event_get_user_data(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected value: %s", buf);

        uint8_t hour = atoi(buf);
        me->date_time.hour = hour;
        time_change_cb(me);
    }
}

static void minute_roller_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target_obj(e);
    time_settings_t *me = (time_settings_t *)lv_event_get_user_data(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected value: %s", buf);

        uint8_t minute = atoi(buf);
        me->date_time.minute = minute;
        time_change_cb(me);
    }
}

static void time_period_roller_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target_obj(e);
    time_settings_t *me = (time_settings_t *)lv_event_get_user_data(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected value: %s", buf);
        if (strcmp(buf, "AM") == 0)
        {
            me->date_time.period = AM;
        }
        else if (strcmp(buf, "PM") == 0)
        {
            me->date_time.period = PM;
        }
    }
}

static void local_time_zone_init(time_settings_t *me, lv_obj_t *parent)
{
    roller_options_init();

    static lv_coord_t col_dsc[] = {
        LV_GRID_FR(2), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),
        LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),
        LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(parent, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(parent, col_dsc, row_dsc);
    lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLLABLE);

    me->year_roller = local_time_zone_roller_create(me, parent, year_options, 0, 0, year_roller_event_handler);
    local_time_zone_label_creat(parent, "年", 1, 0);
    me->month_roller = local_time_zone_roller_create(me, parent, month_options, 2, 0, month_roller_event_handler);
    local_time_zone_label_creat(parent, "月", 3, 0);
    me->day_roller = local_time_zone_roller_create(me, parent, day_options_february_common_year, 4, 0, day_roller_event_handler);
    local_time_zone_label_creat(parent, "日", 5, 0);
    me->hour_roller = local_time_zone_roller_create(me, parent, hour_options_12, 6, 0, hour_roller_event_handler);
    local_time_zone_label_creat(parent, ":", 7, 0);
    me->minute_roller = local_time_zone_roller_create(me, parent, minute_options, 8, 0, minute_roller_event_handler);
    me->time_period_roller = local_time_zone_roller_create(me, parent, time_system_options, 9, 0, time_period_roller_event_handler);
}

static void local_time_zone_enabel_cont_init(time_settings_t *me, lv_obj_t *parent)
{
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(parent, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "本地时间表");
    lv_obj_add_style(label, &label_style, LV_PART_MAIN);
    lv_obj_set_flex_align(label, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t *btn = lv_switch_create(parent);
    lv_obj_set_flex_align(btn, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    me->callback_obj[TIME_PAGE_BTN_LOCAL_TIME_ZONE_ENABLE] = btn;
}

static void _page_load(void *user_data)
{
    time_settings_t *me = (time_settings_t *)user_data;
    lv_scr_load(me->screen);
}

static void main_cont_init(time_settings_t *me)
{
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(3), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(me->main_cont, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(me->main_cont, col_dsc, row_dsc);

    lv_obj_set_style_pad_all(me->main_cont, 0, 0);
    lv_obj_set_style_pad_column(me->main_cont, 0, 0);
    lv_obj_set_style_pad_row(me->main_cont, 0, 0);
    lv_obj_add_style(me->main_cont, &cont_style, 0);

    // time system select cont
    lv_obj_t *time_system_select_cont = lv_obj_create(me->main_cont);
    lv_obj_add_style(time_system_select_cont, &cont_style, 0);
    lv_obj_set_grid_cell(time_system_select_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

    time_system_select_init(me, time_system_select_cont);

    // method of obtaining time
    lv_obj_t *time_obtaning_cont = lv_obj_create(me->main_cont);
    lv_obj_add_style(time_obtaning_cont, &cont_style, 0);
    lv_obj_set_grid_cell(time_obtaning_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);

    time_get_method_select_init(me, time_obtaning_cont);

    // time zone select cont
    lv_obj_t *time_zone_select_cont = lv_obj_create(me->main_cont);
    lv_obj_add_style(time_zone_select_cont, &cont_style, 0);
    lv_obj_set_grid_cell(time_zone_select_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 2, 1);

    local_time_zone_init(me, time_zone_select_cont);

    // local time zone enable
    lv_obj_t *local_time_zone_enable_cont = lv_obj_create(me->main_cont);
    lv_obj_add_style(local_time_zone_enable_cont, &cont_style, 0);
    lv_obj_set_grid_cell(local_time_zone_enable_cont, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 3, 1);

    local_time_zone_enabel_cont_init(me, local_time_zone_enable_cont);
}

void time_settings_date_time_update(time_settings_t *me, date_time_t *date_time)
{
    if (!is_date_time_equal(&me->date_time, date_time))
    {
        me->time_change_cb(date_time);
    }
    me->date_time = *date_time;
    lv_roller_set_selected(me->year_roller, me->date_time.year - ROLLER_YEAR_START, LV_ANIM_OFF);
    lv_roller_set_selected(me->month_roller, me->date_time.month - 1, LV_ANIM_OFF);
    lv_roller_set_selected(me->day_roller, me->date_time.day - 1, LV_ANIM_OFF);
    lv_roller_set_selected(me->hour_roller, me->date_time.hour, LV_ANIM_OFF);
    lv_roller_set_selected(me->minute_roller, me->date_time.minute, LV_ANIM_OFF);
}

static void timer_cb(lv_timer_t *timer)
{
    time_settings_t *me = lv_timer_get_user_data(timer);
    if ((me->get_time_ops.get_date_time_by_ntp && me->get_time_ops.get_date_time_by_local) == NULL)
    {
        LV_LOG_WARN("get_time_ops is NULL");
        return;
    }

    if (me->is_use_ntp == true)
    {
        date_time_t *date_time = me->get_time_ops.get_date_time_by_ntp();
        time_settings_date_time_update(me, date_time);
    }
    else
    {
        date_time_t *date_time = me->get_time_ops.get_date_time_by_local();
        time_settings_date_time_update(me, date_time);
    }
}

void time_settings_timer_init(time_settings_t *me)
{
    lv_timer_t *timer = lv_timer_create(timer_cb, 1000, me);
    lv_timer_ready(timer);
}

lv_obj_t *time_settings_init(time_settings_t *me)
{
    page_style_init();

    // temp set
    me->date_time.year = 2025;
    me->date_time.month = 6;
    me->date_time.day = 18;
    me->date_time.hour = 13;
    me->date_time.minute = 15;
    me->date_time.system = CLOCK_24_HOUR;
    me->date_time.period = AM;

    me->screen = lv_obj_create(NULL);
    lv_obj_add_style(me->screen, &cont_style, LV_PART_MAIN);
    page_manager_register(PAGE_INDEX_TIME, me, _page_load);

    me->main_cont = ui_common_settings_page_create(me->screen, page_title);
    main_cont_init(me);
    time_settings_timer_init(me);
    return me->screen;
}

void time_settings_time_change_cb_register(time_settings_t *me, void (*time_change_cb)(date_time_t *date_time))
{
    me->time_change_cb = time_change_cb;
}

void time_settings_get_time_ops_register(time_settings_t *me, get_time_ops_t *get_time_ops)
{
    me->get_time_ops = *get_time_ops;
}
