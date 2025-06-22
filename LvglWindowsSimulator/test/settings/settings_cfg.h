#ifndef __SETTINGS_PAGE_H
#define __SETTINGS_PAGE_H

#include "./main_settings/settings.h"
#include "./advanced_settings/advanced_settings.h"
#include "./network_settings/network_settings.h"
#include "./network_settings/rs485_settings.h"
#include "./network_settings/wifi_settings.h"
#include "./machine_info/machine_info.h"
#include "./time_settings/time_settings.h"
#include "./scenario_settings/scenario_settings.h"

extern settings_t *settings;
extern advanced_settings_t *advanced_settings;
extern network_settings_t *network_settings;
extern rs485_settings_t *rs485_settings;
extern wifi_settings_t *wifi_settings;
extern machine_info_t *machine_info;
extern time_settings_t *time_settings;
extern scenario_settings_t* scenario_settings;

void settings_cfg(void);
#endif
