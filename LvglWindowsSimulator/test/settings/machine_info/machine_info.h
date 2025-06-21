#ifndef __MACHINE_INFO_H
#define __MACHINE_INFO_H

#include "lvgl.h"

typedef struct
{
    lv_obj_t *screen;
    lv_obj_t *main_cont;

    lv_obj_t *software_version_label;
    lv_obj_t *hardware_version_label;
    lv_obj_t *mac_address_label;
    lv_obj_t *product_type_label;

    lv_obj_t *is_latest_software_version_img;
    lv_obj_t *server_info_img;
} machine_info_t;

lv_obj_t *machine_info_init(machine_info_t *me);

void machine_info_software_version_update(machine_info_t *me, const char *software_version);
void machine_info_hardware_version_update(machine_info_t *me, const char *hardware_version);
void machine_info_mac_address_update(machine_info_t *me, const char *mac_address);
void machine_info_product_type_update(machine_info_t *me, const char *product_type);
void machine_info_is_latest_version_update(machine_info_t *me, bool is_latest_version);
void machine_info_server_info_img_update(machine_info_t *me, void *img_src);

#endif
