#include "lv_page_common.h"
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <time.h>

const int charge_pin = 35;

LV_IMG_DECLARE(cloudy);
LV_IMG_DECLARE(cloudd);
LV_IMG_DECLARE(sunday);
LV_IMG_DECLARE(rain_2);
LV_IMG_DECLARE(rain_1);
LV_IMG_DECLARE(humi_icon);
LV_IMG_DECLARE(temp_icon);
LV_IMG_DECLARE(battery);
LV_IMG_DECLARE(charge);
LV_IMG_DECLARE(hit);

lv_timer_t *timer_time;
struct tm timeinfo;
lv_anim_t a;

static void lv_user_weather_update(lv_obj_t *home_scr)
{
    lv_obj_t *home_weather_img = lv_obj_get_child(home_scr, 2);
    lv_obj_t *home_weather_label = lv_obj_get_child(home_scr, 3);
    lv_obj_t *home_temp_bar = lv_obj_get_child(home_scr, 11);
    lv_obj_t *home_humi_bar = lv_obj_get_child(home_scr, 12);
    lv_obj_t *home_temp_label = lv_obj_get_child(home_scr, 13);
    lv_obj_t *home_humi_label = lv_obj_get_child(home_scr, 14);

    switch (user_weather_info.day_one_text)
    {
    case 0:
        lv_img_set_src(home_weather_img, &sunday);
        break;
    case 4:
        lv_img_set_src(home_weather_img, &cloudy);
        break;
    case 5 ... 9:
        lv_img_set_src(home_weather_img, &cloudd);
        break;
    case 10 ... 12:
        lv_img_set_src(home_weather_img, &rain_1);
        break;
    case 13 ... 18:
        lv_img_set_src(home_weather_img, &rain_2);
        break;
    default:
        lv_img_set_src(home_weather_img, &sunday);
        break;
    }

    lv_label_set_text_fmt(home_weather_label, "%d~%d°C", user_weather_info.day_one_temp_high, user_weather_info.day_one_temp_low);

    lv_bar_set_value(home_temp_bar, user_weather_info.day_one_temp_high, LV_ANIM_ON);
    lv_label_set_text_fmt(home_temp_label, "#0000ff %d°C#", user_weather_info.day_one_temp_high);

    lv_bar_set_value(home_humi_bar, user_weather_info.day_one_humi, LV_ANIM_ON);
    lv_label_set_text_fmt(home_humi_label, "#00ff00 %d%% #", user_weather_info.day_one_humi);
}

static void lv_user_time_update(lv_obj_t *home_scr)
{
    lv_obj_t *home_clock_label = lv_obj_get_child(home_scr, 1);
    lv_obj_t *home_date_label = lv_obj_get_child(home_scr, 6);
    lv_obj_t *home_day_label = lv_obj_get_child(home_scr, 8);

    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }

    lv_label_set_text_fmt(home_clock_label, "%d%d:%d%d", timeinfo.tm_hour / 10, timeinfo.tm_hour % 10, timeinfo.tm_min / 10, timeinfo.tm_min % 10);
    lv_label_set_text_fmt(home_date_label, "%d-%d-%d", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
    switch (timeinfo.tm_wday)
    {
    case 0:
        lv_label_set_text(home_day_label, "周日");
        break;
    case 1:
        lv_label_set_text(home_day_label, "周一");
        break;
    case 2:
        lv_label_set_text(home_day_label, "周二");
        break;
    case 3:
        lv_label_set_text(home_day_label, "周三");
        break;
    case 4:
        lv_label_set_text(home_day_label, "周四");
        break;
    case 5:
        lv_label_set_text(home_day_label, "周五");
        break;
    case 6:
        lv_label_set_text(home_day_label, "周六");
        break;
    default:
        lv_label_set_text(home_day_label, "周六");
        break;
    }
}

static void anim_opa_cb(void *var, int32_t v)
{
    lv_obj_set_style_opa((lv_obj_t*)var, v, 0);
}

static void lv_user_charge_update(lv_obj_t *home_scr)
{
    static bool anmi_created_flag = false;
    lv_obj_t *home_bettery_img;
    lv_obj_t *home_battery_label;
    home_bettery_img = lv_obj_get_child(home_scr, 4);
    home_battery_label = lv_obj_get_child(home_scr, 5);
    if (digitalRead(charge_pin) && anmi_created_flag==true)
    {
        anmi_created_flag = false;
        lv_anim_del(home_bettery_img, anim_opa_cb);
        lv_obj_set_style_opa(home_bettery_img,255,0);
        lv_label_set_text(home_battery_label, "未充电");
        lv_obj_set_style_opa(home_battery_label,255,0);
    }
    if (!digitalRead(charge_pin))
    {
        if (anmi_created_flag==false)
        {
            anmi_created_flag = true;
            lv_anim_init(&a);
            lv_anim_set_var(&a, home_bettery_img);
            lv_anim_set_values(&a, 0, 250);
            lv_anim_set_playback_delay(&a, 500);
            lv_anim_set_playback_time(&a, 500);
            lv_anim_set_repeat_delay(&a, 500);
            lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
            lv_anim_set_exec_cb(&a, anim_opa_cb);
            lv_anim_start(&a);
            lv_label_set_text(home_battery_label, "充电中");
        }
    }
}

static void lv_timer_time_update(lv_timer_t *timer)
{
    Serial.println("hello");
    if (timer->user_data != NULL)
    {
        lv_obj_t *home_scr = (lv_obj_t *)timer->user_data;
        lv_user_time_update(home_scr);
        lv_user_charge_update(home_scr);
    }
}

static void lv_timer_time_stop(void)
{
    Serial.println("time");
    lv_timer_del(timer_time);
}

void lv_app_load_home_scr(void)
{
    pinMode(charge_pin, INPUT_PULLUP);

    static lv_style_t clock_label_style;
    lv_style_init(&clock_label_style);
    lv_style_set_text_font(&clock_label_style, &mynumber);

    static lv_style_t font_16_label_style;
    lv_style_init(&font_16_label_style);
    lv_style_set_text_font(&font_16_label_style, &myfont_16);

    lv_obj_t *home_scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(home_scr, lv_color_white(), 0);

    lv_obj_t *exit_btn = lv_btn_create(home_scr);
    lv_obj_remove_style_all(exit_btn);
    lv_obj_set_size(exit_btn, 1, 1);
    lv_obj_set_align(exit_btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(exit_btn, (lv_event_cb_t)app_exit_event_handler, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(exit_btn, (lv_event_cb_t)lv_timer_time_stop, LV_EVENT_LONG_PRESSED, NULL);

    lv_obj_t *home_clock_label = lv_label_create(home_scr);
    lv_obj_add_style(home_clock_label, &clock_label_style, 0);
    lv_label_set_text(home_clock_label, "12:30");
    lv_obj_align(home_clock_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *home_weather_img = lv_img_create(home_scr);
    lv_img_set_src(home_weather_img, &rain_1);
    lv_obj_align(home_weather_img, LV_ALIGN_TOP_RIGHT, -10, 10);

    lv_obj_t *home_weather_label = lv_label_create(home_scr);
    lv_label_set_text(home_weather_label, "20~32°C");
    lv_obj_align(home_weather_label, LV_ALIGN_TOP_RIGHT, -5, 55);

    lv_obj_t *home_bettery_img = lv_img_create(home_scr);
    lv_img_set_src(home_bettery_img, &charge);
    lv_obj_align(home_bettery_img, LV_ALIGN_TOP_LEFT, 15, 10);

    lv_obj_t *home_battery_label = lv_label_create(home_scr);
    lv_obj_add_style(home_battery_label, &font_16_label_style, 0);
    lv_label_set_text(home_battery_label, "未充电");
    lv_obj_align(home_battery_label, LV_ALIGN_TOP_LEFT, 15, 55);

    lv_obj_t *home_date_label = lv_label_create(home_scr);
    lv_label_set_text(home_date_label, "2021-09-12");
    lv_obj_align(home_date_label, LV_ALIGN_TOP_MID, 0, 15);

    lv_obj_t *home_location_label = lv_label_create(home_scr);
    lv_obj_add_style(home_location_label, &font_16_label_style, 0);
    lv_label_set_text(home_location_label, "武汉");
    lv_obj_align(home_location_label, LV_ALIGN_TOP_MID, -20, 55);

    lv_obj_t *home_day_label = lv_label_create(home_scr);
    lv_obj_add_style(home_day_label, &font_16_label_style, 0);
    lv_label_set_text(home_day_label, "周日");
    lv_obj_align(home_day_label, LV_ALIGN_TOP_MID, 20, 55);

    lv_obj_t *home_temp_img = lv_img_create(home_scr);
    lv_img_set_src(home_temp_img, &temp_icon);
    lv_obj_align(home_temp_img, LV_ALIGN_BOTTOM_LEFT, 10, -40);

    lv_obj_t *home_humi_img = lv_img_create(home_scr);
    lv_img_set_src(home_humi_img, &humi_icon);
    lv_obj_align(home_humi_img, LV_ALIGN_BOTTOM_LEFT, 10, -5);

    static lv_style_t temp_bar_style;
    lv_style_init(&temp_bar_style);
    lv_style_set_bg_opa(&temp_bar_style, LV_OPA_COVER);
    lv_style_set_bg_grad_dir(&temp_bar_style, LV_GRAD_DIR_HOR);

    static lv_style_t humi_bar_style;
    lv_style_init(&humi_bar_style);
    lv_style_set_bg_opa(&humi_bar_style, LV_OPA_COVER);
    lv_style_set_bg_grad_dir(&humi_bar_style, LV_GRAD_DIR_HOR);

    lv_obj_t *home_temp_bar = lv_bar_create(home_scr);
    lv_style_set_bg_color(&temp_bar_style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&temp_bar_style, lv_palette_main(LV_PALETTE_RED));
    lv_obj_add_style(home_temp_bar, &temp_bar_style, LV_PART_INDICATOR);
    lv_obj_set_size(home_temp_bar, 90, 10);
    lv_obj_align(home_temp_bar, LV_ALIGN_BOTTOM_LEFT, 45, -50);
    lv_bar_set_range(home_temp_bar, -10, 42);
    lv_bar_set_value(home_temp_bar, 26, LV_ANIM_ON);

    lv_obj_t *home_humi_bar = lv_bar_create(home_scr);
    lv_style_set_bg_color(&humi_bar_style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&humi_bar_style, lv_palette_main(LV_PALETTE_GREY));
    lv_obj_add_style(home_humi_bar, &humi_bar_style, LV_PART_INDICATOR);
    lv_obj_set_size(home_humi_bar, 90, 10);
    lv_obj_align(home_humi_bar, LV_ALIGN_BOTTOM_LEFT, 45, -15);
    lv_bar_set_range(home_humi_bar, 0, 100);
    lv_bar_set_value(home_humi_bar, 50, LV_ANIM_ON);

    lv_obj_t *home_temp_label = lv_label_create(home_scr);
    lv_label_set_recolor(home_temp_label, true);
    lv_label_set_text(home_temp_label, "#0000ff 26°C#");
    lv_obj_align(home_temp_label, LV_ALIGN_BOTTOM_LEFT, 135, -47);

    lv_obj_t *home_humi_label = lv_label_create(home_scr);
    lv_label_set_recolor(home_humi_label, true);
    lv_label_set_text(home_humi_label, "#00ff00 50%#");
    lv_obj_align(home_humi_label, LV_ALIGN_BOTTOM_LEFT, 135, -12);

    lv_obj_t *home_anmi_img = lv_gif_create(home_scr);
    lv_gif_set_src(home_anmi_img, &hit);
    lv_obj_align(home_anmi_img, LV_ALIGN_BOTTOM_RIGHT, -10, -10);

    static lv_style_t line_style;
    lv_style_init(&line_style);
    lv_style_set_line_width(&line_style, 2);
    lv_style_set_line_color(&line_style, lv_palette_main(LV_PALETTE_GREY));

    static lv_point_t line_1_points[] = {{5, 80}, {235, 80}};
    lv_obj_t *line_1 = lv_line_create(home_scr);
    lv_line_set_points(line_1, line_1_points, 2);
    lv_obj_add_style(line_1, &line_style, 0);

    static lv_point_t line_2_points[] = {{70, 5}, {70, 80}};
    lv_obj_t *line_2 = lv_line_create(home_scr);
    lv_line_set_points(line_2, line_2_points, 2);
    lv_obj_add_style(line_2, &line_style, 0);

    static lv_point_t line_3_points[] = {{170, 5}, {170, 80}};
    lv_obj_t *line_3 = lv_line_create(home_scr);
    lv_line_set_points(line_3, line_3_points, 2);
    lv_obj_add_style(line_3, &line_style, 0);

    static lv_point_t line_4_points[] = {{70, 40}, {170, 40}};
    lv_obj_t *line_4 = lv_line_create(home_scr);
    lv_line_set_points(line_4, line_4_points, 2);
    lv_obj_add_style(line_4, &line_style, 0);

    static lv_point_t line_5_points[] = {{5, 160}, {235, 160}};
    lv_obj_t *line_5 = lv_line_create(home_scr);
    lv_line_set_points(line_5, line_5_points, 2);
    lv_obj_add_style(line_5, &line_style, 0);

    lv_user_time_update(home_scr);
    lv_user_weather_update(home_scr);

    lv_scr_load_anim(home_scr, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);

    timer_time = lv_timer_create(lv_timer_time_update, 1000, home_scr);
}