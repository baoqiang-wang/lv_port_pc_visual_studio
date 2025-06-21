#include "page_manager.h"
#include "ui_common.h"
#include <string.h>
#include "lvgl.h"

page_manager_t Pages[PAGE_INDEX_MAX];
static page_index_t page_stack[PAGE_INDEX_MAX];
static page_index_t page_stack_top;

void push_page(page_index_t index)
{
    if (index < PAGE_INDEX_MAX)
    {
        if (Pages[index].load != NULL)
        {
            Pages[index].load(Pages[index].user_data);
            page_stack_top++;
            page_stack[page_stack_top] = index;
            LV_LOG("Push page stack top: %d", page_stack_top);
            LV_LOG("Push page index: %d", index);
        }
    }
}

void pop_page(void)
{
    if (page_stack_top >= 0)
    {
        page_stack_top--;
        LV_LOG("Pop page stack top: %d", page_stack_top);
        page_index_t index = page_stack[page_stack_top];
        Pages[page_stack_top].load(Pages[page_stack_top].user_data);
    }
    else
    {
        LV_LOG("Pop page stack error");
    }
}

page_index_t current_page(void)
{
    if (page_stack_top >= 0)
    {
        return page_stack[page_stack_top];
    }
}

void page_manager_register(page_index_t index, void *user_data, void (*load)(void *user_data))
{
    LV_ASSERT(index >= 0 && index < PAGE_INDEX_MAX);

    if (user_data == NULL || load == NULL || index < 0 || index >= PAGE_INDEX_MAX)
    {
        return;
    }

    Pages[index].user_data = user_data;
    Pages[index].load = load;
}