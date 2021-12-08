#include "lv_page_common.h"

void lv_app_load_home_scr(void)
{
    LV_IMG_DECLARE(rain_1);
    LV_IMG_DECLARE(humi_icon);
    LV_IMG_DECLARE(temp_icon);
    LV_IMG_DECLARE(battery);
    LV_IMG_DECLARE(charge);
    LV_IMG_DECLARE(xiaohei);

    static lv_style_t clock_label_style;
    lv_style_init(&clock_label_style);
    lv_style_set_text_font(&clock_label_style, &mynumber);

    static lv_style_t font_16_label_style;
    lv_style_init(&font_16_label_style);
    lv_style_set_text_font(&font_16_label_style, &myfont_16);

    lv_obj_t* home_scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(home_scr, lv_color_white(), 0);

    lv_obj_t* exit_btn = lv_btn_create(home_scr);
    lv_obj_remove_style_all(exit_btn);
    lv_obj_set_size(exit_btn, 1, 1);
    lv_obj_set_align(exit_btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(exit_btn, app_exit_event_handler, LV_EVENT_LONG_PRESSED, NULL);

    lv_obj_t* home_clock_label = lv_label_create(home_scr);
    lv_obj_add_style(home_clock_label, &clock_label_style, 0);
    lv_label_set_text(home_clock_label, "12:30");
    lv_obj_align(home_clock_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* home_weather_img = lv_img_create(home_scr);
    lv_img_set_src(home_weather_img, &rain_1);
    lv_obj_align(home_weather_img, LV_ALIGN_TOP_RIGHT, -10, 10);

    lv_obj_t* home_weather_label = lv_label_create(home_scr);
    lv_label_set_text(home_weather_label, "20~32°C");
    lv_obj_align(home_weather_label, LV_ALIGN_TOP_RIGHT, -5, 55);

    lv_obj_t* home_bettery_img = lv_img_create(home_scr);
    lv_img_set_src(home_bettery_img, &charge);
    lv_obj_align(home_bettery_img, LV_ALIGN_TOP_LEFT, 15, 10);

    lv_obj_t* home_battery_label = lv_label_create(home_scr);
    lv_obj_add_style(home_battery_label, &font_16_label_style, 0);
    lv_label_set_text(home_battery_label, "充电中");
    lv_obj_align(home_battery_label, LV_ALIGN_TOP_LEFT, 15, 55);

    lv_obj_t* home_date_label = lv_label_create(home_scr);
    lv_label_set_text(home_date_label, "2021-09-12");
    lv_obj_align(home_date_label, LV_ALIGN_TOP_MID,0,15);

    lv_obj_t* home_location_label = lv_label_create(home_scr);
    lv_obj_add_style(home_location_label, &font_16_label_style, 0);
    lv_label_set_text(home_location_label, "武汉");
    lv_obj_align(home_location_label, LV_ALIGN_TOP_MID, -20, 55);

    lv_obj_t* home_day_label = lv_label_create(home_scr);
    lv_obj_add_style(home_day_label, &font_16_label_style, 0);
    lv_label_set_text(home_day_label, "周日");
    lv_obj_align(home_day_label, LV_ALIGN_TOP_MID, 20, 55);

    lv_obj_t* home_temp_img = lv_img_create(home_scr);
    lv_img_set_src(home_temp_img, &temp_icon);
    lv_obj_align(home_temp_img, LV_ALIGN_BOTTOM_LEFT, 10, -40);

    lv_obj_t* home_humi_img = lv_img_create(home_scr);
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

    lv_obj_t* home_temp_bar = lv_bar_create(home_scr);
    lv_style_set_bg_color(&temp_bar_style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&temp_bar_style, lv_palette_main(LV_PALETTE_RED));
    lv_obj_add_style(home_temp_bar, &temp_bar_style, LV_PART_INDICATOR);
    lv_obj_set_size(home_temp_bar, 90, 10);
    lv_obj_align(home_temp_bar, LV_ALIGN_BOTTOM_LEFT, 45, -50);
    lv_bar_set_range(home_temp_bar, -10, 42);
    lv_bar_set_value(home_temp_bar, 26, LV_ANIM_ON);

    lv_obj_t* home_humi_bar = lv_bar_create(home_scr);
    lv_style_set_bg_color(&humi_bar_style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&humi_bar_style, lv_palette_main(LV_PALETTE_GREY));
    lv_obj_add_style(home_humi_bar, &humi_bar_style, LV_PART_INDICATOR);
    lv_obj_set_size(home_humi_bar, 90, 10);
    lv_obj_align(home_humi_bar, LV_ALIGN_BOTTOM_LEFT, 45, -15);
    lv_bar_set_range(home_humi_bar, 0, 100);
    lv_bar_set_value(home_humi_bar, 50, LV_ANIM_ON);

    lv_obj_t* home_temp_label = lv_label_create(home_scr);
    lv_label_set_recolor(home_temp_label, true);
    lv_label_set_text(home_temp_label,"#0000ff 26°C#");
    lv_obj_align(home_temp_label, LV_ALIGN_BOTTOM_LEFT, 135, -47);

    lv_obj_t* home_humi_label = lv_label_create(home_scr);
    lv_label_set_recolor(home_humi_label, true);
    lv_label_set_text(home_humi_label, "#00ff00 50%#");
    lv_obj_align(home_humi_label, LV_ALIGN_BOTTOM_LEFT,  135, -12);

    lv_obj_t* home_anmi_img = lv_img_create(home_scr);
    lv_img_set_src(home_anmi_img, &xiaohei);
    lv_obj_align(home_anmi_img, LV_ALIGN_BOTTOM_RIGHT, -5, -5);

    static lv_style_t line_style;
    lv_style_init(&line_style);
    lv_style_set_line_width(&line_style, 2);
    lv_style_set_line_color(&line_style, lv_palette_main(LV_PALETTE_GREY));

    static lv_point_t line_1_points[] = { {5,80}, {235,80} };
    lv_obj_t* line_1 = lv_line_create(home_scr);
    lv_line_set_points(line_1, line_1_points, 2);
    lv_obj_add_style(line_1, &line_style, 0);

    static lv_point_t line_2_points[] = { {70,5}, {70,80} };
    lv_obj_t* line_2 = lv_line_create(home_scr);
    lv_line_set_points(line_2, line_2_points, 2);
    lv_obj_add_style(line_2, &line_style, 0);

    static lv_point_t line_3_points[] = { {170,5}, {170,80} };
    lv_obj_t* line_3 = lv_line_create(home_scr);
    lv_line_set_points(line_3, line_3_points, 2);
    lv_obj_add_style(line_3, &line_style, 0);

    static lv_point_t line_4_points[] = { {70,40}, {170,40} };
    lv_obj_t* line_4 = lv_line_create(home_scr);
    lv_line_set_points(line_4, line_4_points, 2);
    lv_obj_add_style(line_4, &line_style, 0);

    static lv_point_t line_5_points[] = { {5,160}, {235,160} };
    lv_obj_t* line_5 = lv_line_create(home_scr);
    lv_line_set_points(line_5, line_5_points, 2);
    lv_obj_add_style(line_5, &line_style, 0);

    lv_scr_load_anim(home_scr, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}