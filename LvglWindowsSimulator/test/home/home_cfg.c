#include "home.h"

home_t *home_page = NULL;
static home_t home_page_ins;

static void _update_tmr_cb(lv_timer_t *tmr)
{
    // static controller_fan_mode_t last_fan_mode;
    // home_t *me = lv_timer_get_user_data(tmr);

    // float cur_temp = controller_current_temperature_get(controller);
    // float set_temp = controller_target_temperature_get(controller);
    // controller_mode_t mode = controller_mode_get(controller);
    // controller_fan_mode_t fan_mode = controller_fan_mode_get(controller);

    // char *cur_text = lv_malloc(sizeof(char) * 5);
    // snprintf(cur_text, 5, "%0.1f", cur_temp);
    // lv_label_set_text(me->cur_temp_label, cur_text);
    // lv_obj_set_style_text_color(me->cur_temp_label, lv_palette_main(LV_PALETTE_BLUE), 0);

    // char *set_text = lv_malloc(sizeof(char) * 10);
    // snprintf(set_text, 5, "%0.1f", set_temp);
    // lv_label_set_text(me->set_temp_label, set_text);
    // lv_obj_set_style_text_color(me->cur_temp_label, lv_palette_main(LV_PALETTE_RED), 0);

    // lv_label_set_text(me->mode_label, mode_str[mode]);

    // if ((fan_mode <= FAN_AUTO) && (last_fan_mode != fan_mode))
    // {
    //     _fan_mode_btn_state_update(me, fan_mode);
    //     last_fan_mode = fan_mode;
    // }

    // lv_free(cur_text);
    // lv_free(set_text);
}

static void home_page_settings_btn_event_handler(lv_event_t *e)
{
}

static void home_page_comfort_mode_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG("Comfort mode button clicked");
    }
}

static void home_page_eco_mode_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG("Eco mode button clicked");
    }
}

static void home_page_heating_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
      
        LV_LOG("Heating button clicked");
    }
}

static void home_page_cooling_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
      
        LV_LOG("Settings button clicked");
    }
}

static void home_page_mode_switching_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    home_t *me = lv_event_get_user_data(e);

    if (code == LV_EVENT_CLICKED)
    {
      

        LV_LOG("mode switching button clicked");
    }
}

static void home_page_low_speed_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    home_t *me = lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED)
    {
      
        LV_LOG("low speed button clicked");
    }
}

static void home_page_medium_speed_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    home_t *me = lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED)
    {
      
        LV_LOG("medium speed button clicked");
    }
}

static void home_page_high_speed_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    home_t *me = lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED)
    {
    
        LV_LOG("high speed button clicked");
    }
}

static void home_page_auto_speed_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    home_t *me = lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED)
    {
       
        LV_LOG("auto speed button clicked");
    }
}

static void home_page_sliding_damper_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        LV_LOG("Slider value changed: %ld", lv_slider_get_value(lv_event_get_current_target(e)));
    }
}

void home_page_cfg(void)
{
    home_page_init(&home_page_ins);
    // home_page_tmr_cb_register(&home_page_ins, _update_tmr_cb);
    home_page = &home_page_ins;
}
