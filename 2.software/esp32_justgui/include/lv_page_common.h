#ifndef __LV_PAGE_COMMON_H
#define __LV_PAGE_COMMON_H



#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

void app_exit_event_handler(lv_event_t* e);

void lv_app_load_home_scr(void);

void lv_app_load_class_scr(void);

void lv_app_load_pc_state_scr(void);

void lv_app_load_wifi_scr(void);

void lv_app_load_weather_scr(void);

void lv_app_load_light_scr(void);

void lv_app_scroll(void);



#endif