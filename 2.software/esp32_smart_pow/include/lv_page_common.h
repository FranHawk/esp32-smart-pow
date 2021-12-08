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

void lv_app_weather_update(void);

void lv_app_load_ble_scr(void);

typedef struct lv_user_weather_info{
    int day_one_text;
    int day_one_temp_high;
    int day_one_temp_low;
    int day_one_year;
    int day_one_month;
    int day_one_date;
    int day_one_humi;
    int day_one_windspeed;
    char day_one_wind_direction[20];
    
    int day_two_text;
    int day_two_temp_high;
    int day_two_temp_low;
    int day_two_year;
    int day_two_month;
    int day_two_date;

    int day_three_text;
    int day_three_temp_high;
    int day_three_temp_low;
    int day_three_year;
    int day_three_month;
    int day_three_date;
}lv_user_weather_info_t;

extern lv_user_weather_info_t user_weather_info;

#endif