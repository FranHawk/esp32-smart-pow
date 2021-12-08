#include "lv_page_common.h"
#include "display.h"
#include <Arduino.h>

extern Display screen;
extern float g_screen_brightness;

static void slider_event_cb(lv_event_t* e)
{
    lv_obj_t* slider = lv_event_get_target(e);
    lv_obj_t* slider_label = (lv_obj_t*)lv_event_get_user_data(e);
    float brightness;
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", lv_slider_get_value(slider));
    lv_label_set_text(slider_label, buf);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    brightness = lv_slider_get_value(slider);
    g_screen_brightness = brightness/100.0;

    screen.setBackLight(g_screen_brightness);
}

void lv_app_load_light_scr(void)
{
    LV_IMG_DECLARE(hei);

    /*Create a transition*/
    static const lv_style_prop_t props[] = { LV_STYLE_BG_COLOR, (lv_style_prop_t)0 };
    static lv_style_transition_dsc_t transition_dsc;
    lv_style_transition_dsc_init(&transition_dsc, props, lv_anim_path_linear, 300, 0, NULL);

    static lv_style_t style_main;
    static lv_style_t style_indicator;
    static lv_style_t style_knob;
    static lv_style_t style_pressed_color;

    static lv_obj_t* slider_label;

    lv_style_init(&style_main);
    lv_style_set_bg_opa(&style_main, LV_OPA_COVER);
    lv_style_set_bg_color(&style_main, lv_color_hex3(0xbbb));
    lv_style_set_radius(&style_main, LV_RADIUS_CIRCLE);
    lv_style_set_pad_ver(&style_main, -2); /*Makes the indicator larger*/

    lv_style_init(&style_indicator);
    lv_style_set_bg_opa(&style_indicator, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indicator, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_radius(&style_indicator, LV_RADIUS_CIRCLE);
    lv_style_set_transition(&style_indicator, &transition_dsc);

    lv_style_init(&style_knob);
    lv_style_set_bg_opa(&style_knob, LV_OPA_COVER);
    lv_style_set_bg_color(&style_knob, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_border_color(&style_knob, lv_palette_darken(LV_PALETTE_YELLOW, 3));
    lv_style_set_border_width(&style_knob, 2);
    lv_style_set_radius(&style_knob, LV_RADIUS_CIRCLE);
    lv_style_set_pad_all(&style_knob, 6); /*Makes the knob larger*/
    lv_style_set_transition(&style_knob, &transition_dsc);

    lv_style_init(&style_pressed_color);
    lv_style_set_bg_color(&style_pressed_color, lv_palette_darken(LV_PALETTE_YELLOW, 2));

    /*Create a slider and add the style*/
    lv_obj_t* light_scr = lv_obj_create(NULL);

    lv_obj_t* exit_btn = lv_btn_create(light_scr);
    lv_obj_remove_style_all(exit_btn);
    lv_obj_set_size(exit_btn, 1, 1);
    lv_obj_set_align(exit_btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(exit_btn, app_exit_event_handler, LV_EVENT_LONG_PRESSED, NULL);

    lv_obj_t* slider = lv_slider_create(light_scr);
    lv_obj_remove_style_all(slider);        /*Remove the styles coming from the theme*/
    lv_obj_set_size(slider, 150, 20);
    lv_slider_set_value(slider, (int)(g_screen_brightness*100), LV_ANIM_ON);

    slider_label = lv_label_create(light_scr);
    lv_label_set_text_fmt(slider_label, "%d%%",(int)(g_screen_brightness*100));
    lv_obj_set_align(slider, LV_ALIGN_CENTER);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, slider_label);

    lv_obj_add_style(slider, &style_main, LV_PART_MAIN);
    lv_obj_add_style(slider, &style_indicator, LV_PART_INDICATOR);
    lv_obj_add_style(slider, &style_pressed_color, LV_PART_INDICATOR | LV_STATE_PRESSED);
    lv_obj_add_style(slider, &style_knob, LV_PART_KNOB);
    lv_obj_add_style(slider, &style_pressed_color, LV_PART_KNOB | LV_STATE_PRESSED);

    

    lv_obj_center(slider);

    lv_obj_t* hei_img;
    hei_img = lv_gif_create(light_scr);
    lv_gif_set_src(hei_img,&hei);
    lv_obj_align(hei_img, LV_ALIGN_CENTER,0,-50);

    lv_scr_load_anim(light_scr, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}