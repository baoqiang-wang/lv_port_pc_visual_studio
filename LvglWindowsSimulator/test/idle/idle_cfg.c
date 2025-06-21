#include "idle_page.h"

idle_page_t *idle_page;
static idle_page_t idle_page_ins;

void idle_page_cfg(void)
{
    idle_page_init(&idle_page_ins);
    idle_page = &idle_page_ins;
}