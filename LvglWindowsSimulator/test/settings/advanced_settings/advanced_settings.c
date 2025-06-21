/*
 * @file advanced_settings.c
 * Created on Tue Jun 10 2025
 * @author Baoqiang WANG, wangbaoqiang.1@outlook.com
 * Copyright (c) Tue Jun 10 2025 CUBIC
 */

#include "advanced_settings.h"
#include "../../ui_manager/page_manager.h"
#include "../../ui_manager/ui_common.h"
#include <string.h>

static const char *page_title = "高级设置";

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
/**
 * container_of - 获取包含某个成员的结构体指针
 * @ptr: 指向结构体成员的指针
 * @type: 结构体类型
 * @member: 结构体中的成员名
 *
 * 通过已知的结构体成员指针，返回包含该成员的结构体指针。
 */
#include <stddef.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

typedef struct
{
    parent_config_item_t type;
    child_config_item_t start;
    child_config_item_t end;
} parent_config_t;

const char *child_config_item_name[CONFIG_SET_MAX] = {
    "两管制风盘",
    "四管制风盘",
    "二合一",
    "自动",
    "手动",
    "地暖+风盘",
    "地暖",
    "风盘",
    "常开型",
    "常闭型",
    "风机停止(DB)",
    "风机继续运行(DA)",
    "无锁定",
    "密码锁定",
    "开机",
    "关机",
    "记忆",
    "0°C",
    "1°C",
    "2°C",
    "3°C",
    "启动防冻",
    "-",
    "xx°C",
    "+",
    "拔卡后闭合",
    "插卡后闭合",
    "1°C",
    "2°C",
    "3°C",
    "单内置",
    "单外置",
    "本地",
    "网络",
    "启用本地传感器",
    "报故障码",
    "两线阀",
    "三线阀",
    "外置温度传感器",
    "门卡",
    "无",
    "-",
    "xx°C",
    "+",
    "-",
    "xx°C",
    "+",
    "联动风机",
    "联动阀门",
    "无",
    "-",
    "xx°C",
    "+",
    "节能模式",
    "开关机",
    "无",
    "恢复出厂设置",
    "解绑所有APP关联用户",
    "恢复服务器设置",
};

const char *parent_config_item_name[ITEM_MAX] = {
    "设备类型",
    "四管制冷热切换方式",
    "二合一机型供暖方式",
    "二合一地暖阀类型",
    "室温达到设定值",
    "按键锁定",
    "掉电记忆",
    "四管制死区",
    "防冻保护",
    "防冻保护设置",
    "门卡设置",
    "回差设定",
    "传感器类型",
    "显示温度来源",
    "网络温度故障处理",
    "风盘阀门类型",
    "干接点输入",
    "温度设定上限",
    "温度设定下限",
    "联动输出设置",
    "温度显示修正",
    "门卡联动功能",
    "其他设置",
};

parent_config_t configuration[ITEM_MAX] = {
    {.type = PARENT_SET_DEVICE_TYPE, .start = CONFIG_SET_DEVICE_TYPE_TWO_COIL, .end = CONFIG_SET_DEVICE_TYPE_TWO_IN_ONE},
    {.type = PARENT_SET_COOL_AND_HEAT_SWITCH_METHOD, .start = CONFIG_SET_AUTO, .end = CONFIG_SET_MANUAL},
    {.type = PARENT_SET_HEATING_METHOD, .start = CONFIG_SET_HEATING_METHOD_UNDERFLOOR_AND_FAN, .end = CONFIG_SET_HEATING_METHOD_FAN_COIL},
    {.type = PARENT_SET_UNDERFLOOR_HEATING_VALVE_TYPE, .start = CONFIG_SET_UNDERFLOOR_HEATING_NORMALLY_OPEN, .end = CONFIG_SET_UNDERFLOOR_HEATING_NORMALLY_CLOSED},
    {.type = PARENT_SET_TEMP_REACHED_SET_VALUE, .start = CONFIG_SET_DB, .end = CONFIG_SET_DA},
    {.type = PARENT_SET_BTN_LOCK, .start = CONFIG_SET_BTN_NO_LOCK, .end = CONFIG_SET_BTN_PWD_LOCK},
    {.type = PARENT_SET_FOUR_COIL_DEADBAND, .start = CONFIG_SET_FORU_COIL_DEADBAND_A, .end = CONFIG_SET_FORU_COIL_DEADBAND_D},
    {.type = PARENT_SET_POWER_DOWN_MEMORY, .start = CONFIG_SET_PWR_DOWN_TURN_ON, .end = CONFIG_SET_PWR_DOWN_MEMORY},
    {.type = PARENT_SET_LOW_TEMP_PROTECT_ENABLE, .start = CONFIG_SET_LOW_PROTECT_ENABEL, .end = CONFIG_SET_LOW_PROTECT_ENABEL},
    {.type = PARENT_SET_LOW_TEMP_PROTECT_SET, .start = CONFIG_SET_LOW_PROTECT_DOWN, .end = CONFIG_SET_LOW_PROTECT_UP},
    {.type = PARENT_SET_DOOR_CARD_SET, .start = CONFIG_SET_REMOVE_DOOR_CARD, .end = CONFIG_SET_INSERT_DOOR_CARD},
    {.type = PARENT_SET_HYSTERESIS_SET, .start = CONFIG_SET_HYSTERESIS_A, .end = CONFIG_SET_HYSTERESIS_C},
    {.type = PARENT_SET_SENSOR_TYPE, .start = CONFIG_SET_SENSOR_INTERNAL, .end = CONFIG_SET_SENSOR_EXTERNAL},
    {.type = PARENT_SET_DISP_TEMP, .start = CONFIG_SET_DISP_TEMP_LOCAL, .end = CONFIG_SET_DISP_TEMP_NETWORK},
    {.type = PARENT_SET_NET_TEMP_ERR, .start = CONFIG_SET_TEMP_ERR_LOCAL_SENSOR, .end = CONFIG_SET_TEMP_ERR_FAULT_CODE},
    {.type = PARENT_SET_VALVE_TYPE, .start = CONFIG_SET_TWO_WIRE, .end = CONFIG_SET_THREE_WIRE},
    {.type = PARENT_SET_DRY_CONTACT_INPUT, .start = CONFIG_SET_DRY_CONTACT_EXTERNAL_SENSOR, .end = CONFIG_SET_DRY_CONTACT_NONE},
    {.type = PARENT_SET_TEMP_MAX_LIMIT, .start = CONFIG_SET_TEMP_MAX_LIMIT_DOWN, .end = CONFIG_SET_TEMP_MAX_LIMIT_UP},
    {.type = PARENT_SET_TEMP_MIN_LIMIT, .start = CONFIG_SET_TEMP_MIN_LIMIT_DOWN, .end = CONFIG_SET_TEMP_MIN_LIMIT_UP},
    {.type = PARENT_SET_LINKED_OUTPUT_SET, .start = CONFIG_SET_LINKED_OUTPUT_SETTINGS_FAN, .end = CONFIG_SET_LINKED_OUTPUT_SETTINGS_NONE},
    {.type = PARENT_SET_DISP_TEMP_CORRECTION, .start = CONFIG_SET_TEMP_DISP_CORRECTION_DOWN, .end = CONFIG_SET_TEMP_DISP_CORRECTION_UP},
    {.type = PARENT_SET_DOOR_CARD_LINKED_FUN, .start = CONFIG_SET_DOOR_CARD_LINKED_FUN_ECO, .end = CONFIG_SET_DOOR_CARD_LINKED_FUN_NONE},
    {.type = PARENT_SET_OTHERS, .start = CONFIG_SET_FACTORY_RESET, .end = CONFIG_SET_SERVER_SETTINGS_RESET},
};

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

static void print_memory_usage(void)
{
    lv_mem_monitor_t mem_info;
    lv_mem_monitor(&mem_info);

    LV_LOG_USER("Total heap size: %u bytes", (unsigned int)mem_info.total_size);
    LV_LOG_USER("Free memory blocks: %u", (unsigned int)mem_info.free_cnt);
    LV_LOG_USER("Free memory size: %u bytes", (unsigned int)mem_info.free_size);
    LV_LOG_USER("Biggest free block: %u bytes", (unsigned int)mem_info.free_biggest_size);
    LV_LOG_USER("Used memory blocks: %u", (unsigned int)mem_info.used_cnt);
    LV_LOG_USER("Max used memory: %u bytes", (unsigned int)mem_info.max_used);
    LV_LOG_USER("Memory usage percentage: %u%%", (unsigned int)mem_info.used_pct);
    LV_LOG_USER("Fragmentation percentage: %u%%", (unsigned int)mem_info.frag_pct);
}

static void _pwd_config_cont_switch(advanced_settings_t *me, lv_obj_t *active_cont)
{
    LV_LOG("Password is %s", me->password);
    if (active_cont == (me->config_cont))
    {
        lv_obj_add_flag(me->pwd_cont, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(me->config_cont, LV_OBJ_FLAG_HIDDEN);
    }
    else if (active_cont == (me->pwd_cont))
    {
        lv_obj_add_flag(me->config_cont, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(me->pwd_cont, LV_OBJ_FLAG_HIDDEN);
    }
}

static void _configuration_tiem_create(advanced_settings_t *me, parent_config_t *config_item)
{
    lv_obj_t *main_cont = lv_obj_create(me->config_cont);

    lv_obj_set_width(main_cont, LV_PCT(100));
    lv_obj_set_height(main_cont, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(main_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(main_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_bg_color(main_cont, lv_color_black(), 0);

    lv_obj_set_style_pad_top(main_cont, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(main_cont, 10, LV_PART_MAIN);
    lv_obj_set_style_border_side(main_cont, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
    lv_obj_set_style_border_width(main_cont, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(main_cont, lv_color_hex(0xafafaf), LV_PART_MAIN);

    lv_obj_t *title_cont = lv_label_create(main_cont);
    lv_label_set_text(title_cont, parent_config_item_name[config_item->type]);
    lv_obj_set_style_text_font(title_cont, &lv_font_CN_Bold_2, 0);
    lv_obj_set_style_text_color(title_cont, lv_color_white(), 0);
    lv_obj_set_width(title_cont, LV_PCT(100));

    lv_obj_t *group_cont = lv_obj_create(main_cont);
    lv_obj_remove_style_all(group_cont);
    lv_obj_set_width(group_cont, LV_PCT(100));
    lv_obj_set_height(group_cont, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(group_cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_top(group_cont, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(group_cont, 10, LV_PART_MAIN);

    for (int i = config_item->start; i <= config_item->end; i++)
    {
        lv_obj_t *btn_cont = lv_obj_create(group_cont);
        lv_obj_remove_style_all(btn_cont);
        lv_obj_set_width(btn_cont, LV_SIZE_CONTENT);
        lv_obj_set_height(btn_cont, LV_SIZE_CONTENT);
        lv_obj_set_style_pad_left(btn_cont, 10, LV_PART_MAIN);
        lv_obj_set_style_pad_top(btn_cont, 5, LV_PART_MAIN);
        lv_obj_set_style_pad_bottom(btn_cont, 10, LV_PART_MAIN);
        lv_obj_set_flex_flow(btn_cont, LV_FLEX_FLOW_ROW_WRAP);
        lv_obj_set_flex_align(btn_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

        lv_obj_t *btn = lv_button_create(btn_cont);
        lv_obj_set_size(btn, 30, 30);
        lv_obj_set_style_radius(btn, 15, LV_PART_MAIN);
        set_button_style(btn, 0);

        lv_obj_t *label = lv_label_create(btn_cont);
        lv_obj_set_style_text_font(label, &lv_font_CN_Bold_2, 0);
        lv_obj_set_style_pad_left(label, 5, LV_PART_MAIN);
        lv_label_set_text(label, child_config_item_name[i]);
        lv_obj_set_style_text_color(label, lv_color_white(), 0);

        me->callback_obj[i] = btn;
    }
}

static void _configuration_module_init(advanced_settings_t *me)
{
    me->config_cont = lv_list_create(me->main_cont);
    lv_obj_add_flag(me->config_cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_size(me->config_cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(me->config_cont, lv_color_black(), 0);
    lv_obj_set_style_border_width(me->config_cont, 0, 0);
    lv_obj_center(me->config_cont);

    lv_obj_set_style_pad_all(me->config_cont, 0, 0);
    lv_obj_set_style_pad_column(me->config_cont, 0, 0);
    lv_obj_set_style_pad_row(me->config_cont, 0, 0);

    LV_LOG("%d configuration items need to be generated.", ARRAY_SIZE(configuration));
    for (int i = 0; i < ARRAY_SIZE(configuration); i++)
    {
        _configuration_tiem_create(me, &configuration[i]);
    }
}

static void configuration_context_adjust(advanced_settings_t *me, child_config_item_t index)
{
    lv_obj_t *pre_btn = me->callback_obj[index - 1];
    lv_obj_t *cur_btn = me->callback_obj[index];
    lv_obj_t *next_btn = me->callback_obj[index + 1];

    lv_obj_t *pre_cont = lv_obj_get_parent(pre_btn);
    lv_obj_t *cur_cont = lv_obj_get_parent(cur_btn);
    lv_obj_t *next_cont = lv_obj_get_parent(next_btn);

    lv_obj_t *main_cont = lv_obj_get_parent(pre_cont);

    lv_obj_t *pre_label = lv_obj_get_child(pre_cont, 1);
    lv_obj_t *cur_label = lv_obj_get_child(cur_cont, 1);
    lv_obj_t *next_label = lv_obj_get_child(next_cont, 1);

    lv_obj_del(pre_label);
    lv_obj_del(cur_btn);
    lv_obj_del(next_label);

    lv_obj_t *new_pre_label = lv_label_create(pre_btn);
    lv_obj_t *new_next_label = lv_label_create(next_btn);
    lv_obj_center(new_pre_label);
    lv_obj_center(new_next_label);
    lv_obj_center(cur_label);

    lv_label_set_text(new_pre_label, "-");
    lv_label_set_text(new_next_label, "+");
    lv_label_set_text(cur_label, "5°C");
    lv_obj_set_flex_flow(main_cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(main_cont,
                          LV_FLEX_ALIGN_SPACE_EVENLY, // 主轴上均匀分布
                          LV_FLEX_ALIGN_CENTER,       // 交叉轴上居中
                          LV_FLEX_ALIGN_START);       // 轨道整体靠顶部对齐
}

static void _advanced_settings_enter(advanced_settings_t *me)
{
    lv_obj_add_flag(me->pwd_cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(me->config_cont, LV_OBJ_FLAG_HIDDEN);
}

static void textarea_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    advanced_settings_t *me = lv_event_get_user_data(e);

    if (code == LV_EVENT_FOCUSED)
    {
        lv_keyboard_set_textarea(me->pwd_kb, ta);
        lv_obj_remove_flag(me->pwd_kb, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(me->input_err_prompt, "输入密码");
    }

    if (code == LV_EVENT_READY)
    {
        const char *pwd = lv_textarea_get_text(ta);
        if (strcmp(pwd, "1234") == 0)
        {
            lv_label_set_text(me->input_err_prompt, "密码正确!");
            lv_obj_set_style_text_color(me->input_err_prompt, lv_color_hex(0x00d366), LV_PART_MAIN);
            LV_LOG("Password correct!");
            _advanced_settings_enter(me);
        }
        else
        {
            lv_label_set_text(me->input_err_prompt, "密码错误!");
            lv_obj_set_style_text_color(me->input_err_prompt, lv_color_hex(0xDC143C), LV_PART_MAIN);
            lv_textarea_set_text(ta, "");
            LV_LOG("Wrong password!");
        }
    }

    if (code == LV_EVENT_CANCEL)
    {
        lv_keyboard_set_textarea(me->pwd_kb, NULL);
        lv_obj_add_flag(me->pwd_kb, LV_OBJ_FLAG_HIDDEN);
    }
}

static void _password_module_init(advanced_settings_t *me)
{
    me->pwd_cont = lv_obj_create(me->main_cont);
    lv_obj_add_flag(me->pwd_cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_size(me->pwd_cont, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(me->pwd_cont, lv_color_black(), 0);
    lv_obj_set_style_border_width(me->pwd_cont, 0, 0);
    lv_obj_center(me->pwd_cont);

    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(2), LV_GRID_FR(7), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_layout(me->pwd_cont, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(me->pwd_cont, col_dsc, row_dsc);
    lv_obj_clear_flag(me->pwd_cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(me->pwd_cont, 0, 0);
    lv_obj_set_style_pad_column(me->pwd_cont, 0, 0);
    lv_obj_set_style_pad_row(me->pwd_cont, 0, 0);

    me->input_err_prompt = lv_label_create(me->pwd_cont);
    lv_obj_set_style_text_color(me->input_err_prompt, lv_color_hex(0x00d366), LV_PART_MAIN);
    lv_obj_set_style_text_font(me->input_err_prompt, &lv_font_CN_Bold_2, LV_PART_MAIN);
    lv_label_set_text(me->input_err_prompt, "输入密码");
    lv_obj_set_grid_cell(me->input_err_prompt, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    me->pwd_ta = lv_textarea_create(me->pwd_cont);
    lv_textarea_set_password_mode(me->pwd_ta, true);
    lv_obj_set_style_text_font(me->pwd_ta, &lv_font_CN_Bold_2, LV_PART_MAIN);
    lv_textarea_set_text(me->pwd_ta, "");
    lv_textarea_set_one_line(me->pwd_ta, true);
    lv_obj_set_style_bg_grad_color(me->pwd_ta, lv_color_black(), 0);
    lv_obj_set_grid_cell(me->pwd_ta, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);

    me->pwd_kb = lv_keyboard_create(me->pwd_cont);
    lv_keyboard_set_mode(me->pwd_kb, LV_KEYBOARD_MODE_NUMBER);
    lv_obj_set_grid_cell(me->pwd_kb, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
    lv_obj_set_style_bg_grad_color(me->pwd_ta, lv_color_black(), 0);
    lv_obj_set_style_text_color(me->pwd_kb, lv_color_white(), 0);

    lv_keyboard_set_textarea(me->pwd_kb, me->pwd_ta);
    lv_obj_add_event_cb(me->pwd_ta, textarea_event_cb, LV_EVENT_ALL, me);
    strncpy(me->password, "123456", sizeof(me->password) - 1);
    me->password[sizeof(me->password) - 1] = '\0';
    LV_LOG("Password module init success");
}

static lv_obj_t *_advanced_settings_grid_set(lv_obj_t *page)
{
    lv_obj_t *screen = lv_obj_create(page);
    lv_obj_set_grid_cell(screen, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    return screen;
}

static advanced_settings_t *_advanced_settings_clasee_init(lv_obj_t *page)
{
    advanced_settings_t *me = (advanced_settings_t *)lv_malloc(sizeof(advanced_settings_t));
    if (me == NULL)
    {
        return NULL;
    }
    memset(me, 0, sizeof(advanced_settings_t));
    return me;
}

static inline advanced_settings_t *to_advanced_settings(lv_obj_t *obj)
{
    return (advanced_settings_t *)((char *)obj - offsetof(advanced_settings_t, screen));
}

void advanced_settings_load(void *user_data)
{
    advanced_settings_t *me = (advanced_settings_t *)user_data;

    lv_obj_t *prompt = lv_obj_get_child(me->pwd_cont, 0);
    lv_obj_t *ta = lv_obj_get_child(me->pwd_cont, 1);
    lv_obj_t *kb = lv_obj_get_child(me->pwd_cont, 2);
    lv_label_set_text(prompt, "输入密码");
    lv_textarea_set_text(ta, "");
    _pwd_config_cont_switch(me, me->pwd_cont);

    lv_scr_load(me->screen);
}

lv_obj_t *advanced_settings_init(advanced_settings_t *me)
{
    memset(me, 0, sizeof(advanced_settings_t));

    me->screen = lv_obj_create(NULL);
    page_manager_register(PAGE_INDEX_ADVANCED, me, advanced_settings_load);

    lv_obj_set_style_bg_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_opa(me->screen, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(me->screen, 0, 0);

    me->main_cont = ui_common_settings_page_create(me->screen, page_title);
    _password_module_init(me);
    _configuration_module_init(me);
    configuration_context_adjust(me, CONFIG_SET_LOW_PROTECT_DATA);
    configuration_context_adjust(me, CONFIG_SET_TEMP_MAX_LIMIT_DATA);
    configuration_context_adjust(me, CONFIG_SET_TEMP_MIN_LIMIT_DATA);
    configuration_context_adjust(me, CONFIG_SET_TEMP_DISP_CORRECTION_DATA);
    return me->screen;
}
