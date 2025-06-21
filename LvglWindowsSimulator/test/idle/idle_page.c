/*
 * @file idle_page.c
 * Created on Mon Jun 09 2025
 * @author Baoqiang WANG, wangbaoqiang.1@outlook.com
 * Copyright (c) Mon Jun 09 2025 CUBIC
 */
#include "idle_page.h"
#include "lvgl.h"
#include "../ui_manager/ui_common.h"
#include "../icons/ui_icons.h"

#define USE_ICON_FOR_BTN 1

static lv_obj_t *_create_idle_page_scr(void)
{
    // 获取活动屏幕
    lv_obj_t *scr = lv_scr_act();

    // 创建一个样式并设置其背景颜色
    static lv_style_t style_bg;
    lv_style_init(&style_bg);
    lv_style_set_bg_color(&style_bg, lv_color_hex(0x131619)); // 设置背景颜色
    lv_style_set_bg_opa(&style_bg, LV_OPA_COVER);             // 确保背景完全不透明

    lv_obj_add_style(scr, &style_bg, 0);
    return scr;
}

static lv_obj_t *_create_power_button(lv_obj_t *parent)
{
    // 创建按钮对象
    lv_obj_t *btn = lv_button_create(parent);
    lv_obj_set_size(btn, 150, 150); // 设置为正方形大小，用于圆形
    lv_obj_center(btn);             // 居中显示

    // 初始化按钮样式
    static lv_style_t style_btn;
    lv_style_init(&style_btn);

    // 设置为圆形
    lv_style_set_radius(&style_btn, LV_RADIUS_CIRCLE);

    // 背景设置：透明填充
    lv_style_set_bg_opa(&style_btn, LV_OPA_0); // 完全透明背景

    // 边框设置：白色线条勾勒
    lv_style_set_border_color(&style_btn, lv_color_white());
    lv_style_set_border_width(&style_btn, 2);
    lv_style_set_border_opa(&style_btn, LV_OPA_80);

    // 阴影可选（增强立体感）
    lv_style_set_shadow_width(&style_btn, 5);
    lv_style_set_shadow_color(&style_btn, lv_color_black());
    lv_style_set_shadow_opa(&style_btn, LV_OPA_30);

    // 添加按压状态反馈（例如边框变蓝）
    static lv_style_t style_pressed;
    lv_style_init(&style_pressed);
    lv_style_set_border_color(&style_pressed, lv_color_hex(0x00aaff)); // 浅蓝色边框
    lv_style_set_text_color(&style_pressed, lv_color_hex(0x00aaff));   // 图标也变色

    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_style(btn, &style_pressed, LV_STATE_PRESSED);

#if USE_ICON_FOR_BTN
    lv_obj_t *icon = lv_img_create(btn);
    lv_img_set_src(icon, &power_icon);
    lv_obj_center(icon);
#else
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_POWER);
    lv_obj_center(label);
    lv_style_set_text_color(&style_btn, lv_color_white()); // 设置图标为白色
    lv_obj_add_style(label, &style_btn, 0);
    lv_style_set_text_font(&style_btn, &lv_font_montserrat_32); // 使用较大的字体大小
#endif

    return btn;
}

void idle_page_init(idle_page_t *me)
{
    me->screen = _create_idle_page_scr();
    lv_obj_t *pwr_btn = _create_power_button(me->screen);
    me->callback_obj[IDLE_PAGE_BTN_PWR] = pwr_btn;
}
