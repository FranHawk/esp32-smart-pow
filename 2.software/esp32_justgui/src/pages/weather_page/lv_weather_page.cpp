#include "lv_page_common.h"

void lv_app_load_weather_scr(void)
{
    LV_IMG_DECLARE(rain_1);
    LV_IMG_DECLARE(rain_2);
    LV_IMG_DECLARE(sunday);
    LV_IMG_DECLARE(cloudd);
    LV_IMG_DECLARE(cloudy);

    static lv_style_t font_16_label_style;
    lv_style_init(&font_16_label_style);
    lv_style_set_text_font(&font_16_label_style, &myfont_16);

    lv_obj_t* weather_scr = lv_obj_create(NULL);

    lv_obj_t* exit_btn = lv_btn_create(weather_scr);
    lv_obj_remove_style_all(exit_btn);
    lv_obj_set_size(exit_btn, 1, 1);
    lv_obj_set_align(exit_btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(exit_btn, app_exit_event_handler, LV_EVENT_LONG_PRESSED, NULL);

    lv_obj_t* weather_day_one = lv_obj_create(weather_scr);
    lv_obj_set_size(weather_day_one, 220, 120);
    lv_obj_align_to(weather_day_one, weather_scr, LV_ALIGN_CENTER, 0, -55);

    lv_obj_t* weather_day_two = lv_obj_create(weather_scr);
    lv_obj_set_size(weather_day_two, 105, 100);
    lv_obj_align_to(weather_day_two, weather_scr, LV_ALIGN_CENTER, -55, 60);

    lv_obj_t* weather_day_three = lv_obj_create(weather_scr);
    lv_obj_set_size(weather_day_three, 105, 100);
    lv_obj_align_to(weather_day_three, weather_scr, LV_ALIGN_CENTER, 55, 60);

    lv_obj_t* weather_day_one_img = lv_img_create(weather_day_one);
    lv_img_set_src(weather_day_one_img, &cloudd);
    lv_obj_align_to(weather_day_one_img, weather_day_one, LV_ALIGN_TOP_LEFT, 20, 0);

    lv_obj_t* weather_day_one_temp = lv_label_create(weather_day_one);
    lv_label_set_text(weather_day_one_temp, "18~26°C");
    lv_obj_align_to(weather_day_one_temp, weather_day_one, LV_ALIGN_LEFT_MID, 20, 10);

    lv_obj_t* weather_day_one_location = lv_label_create(weather_day_one);
    lv_obj_add_style(weather_day_one_location, &font_16_label_style, 0);
    lv_label_set_text(weather_day_one_location, "武汉");
    lv_obj_align_to(weather_day_one_location, weather_day_one, LV_ALIGN_BOTTOM_LEFT, 20, 0);

    lv_obj_t* weather_day_one_date = lv_label_create(weather_day_one);
    lv_label_set_text(weather_day_one_date, "2021-9-26");
    lv_obj_align_to(weather_day_one_date, weather_day_one, LV_ALIGN_TOP_RIGHT, -20, 20);

    lv_obj_t* weather_day_one_humi = lv_label_create(weather_day_one);
    lv_obj_add_style(weather_day_one_humi, &font_16_label_style, 0);
    lv_label_set_text(weather_day_one_humi, "湿度:");
    lv_obj_align_to(weather_day_one_humi, weather_day_one, LV_ALIGN_RIGHT_MID, -50, 10);

    lv_obj_t* weather_day_one_humi_num = lv_label_create(weather_day_one);
    lv_label_set_text(weather_day_one_humi_num, "56%");
    lv_obj_align_to(weather_day_one_humi_num, weather_day_one, LV_ALIGN_RIGHT_MID, -10, 10);

    lv_obj_t* weather_day_one_wind_direction = lv_label_create(weather_day_one);
    lv_obj_add_style(weather_day_one_wind_direction, &font_16_label_style, 0);
    lv_label_set_text(weather_day_one_wind_direction, "风向:东北");
    lv_obj_align_to(weather_day_one_wind_direction, weather_day_one, LV_ALIGN_BOTTOM_RIGHT, -60, 0);

    lv_obj_t* weather_day_one_wind_speed = lv_label_create(weather_day_one);
    lv_obj_add_style(weather_day_one_wind_speed, &font_16_label_style, 0);
    lv_label_set_text(weather_day_one_wind_speed, "风速:6.5");
    lv_obj_align_to(weather_day_one_wind_speed, weather_day_one, LV_ALIGN_BOTTOM_RIGHT, 0, 0);

    lv_obj_t* weather_day_two_img = lv_img_create(weather_day_two);
    lv_img_set_src(weather_day_two_img, &sunday);
    lv_obj_align_to(weather_day_two_img, weather_day_two, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* weather_day_two_date = lv_label_create(weather_day_two);
    lv_label_set_text(weather_day_two_date, "9-27");
    lv_obj_align_to(weather_day_two_date, weather_day_two, LV_ALIGN_TOP_MID, 0, -5);

    lv_obj_t* weather_day_two_temp = lv_label_create(weather_day_two);
    lv_label_set_text(weather_day_two_temp, "18~26°C");
    lv_obj_align_to(weather_day_two_temp, weather_day_two, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_t* weather_day_three_img = lv_img_create(weather_day_three);
    lv_img_set_src(weather_day_three_img, &rain_1);
    lv_obj_align_to(weather_day_three_img, weather_day_three, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* weather_day_three_date = lv_label_create(weather_day_three);
    lv_label_set_text(weather_day_three_date, "9-28");
    lv_obj_align_to(weather_day_three_date, weather_day_three, LV_ALIGN_TOP_MID, 0, -5);

    lv_obj_t* weather_day_three_temp = lv_label_create(weather_day_three);
    lv_label_set_text(weather_day_three_temp, "18~26°C");
    lv_obj_align_to(weather_day_three_temp, weather_day_three, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_scr_load_anim(weather_scr, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}