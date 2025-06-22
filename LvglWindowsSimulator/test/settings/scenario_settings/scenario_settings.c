#include "scenario_settings.h"
#include "../../ui_manager/page_manager.h"
#include "../../ui_manager/ui_common.h"
#include "../../icons/ui_icons.h"

static const char *page_title = "情景模式";


static void _page_loard(void* user_data)
{
    scenario_settings_t* me = (scenario_settings_t*)user_data;
    lv_scr_load(me->screen);
}

lv_obj_t* scenario_settings_init(scenario_settings_t* me)
{
    me->screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_opa(me->screen, LV_OPA_TRANSP, LV_PART_MAIN);
    page_manager_register(PAGE_INDEX_SCENARIO, me, _page_loard);

    me->main_cont = ui_common_settings_page_create(me->screen, page_title);
    lv_obj_set_style_bg_opa(me->main_cont, LV_OPA_TRANSP, LV_PART_MAIN);
}
