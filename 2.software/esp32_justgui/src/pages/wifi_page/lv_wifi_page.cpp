#include "lv_page_common.h"

void lv_app_load_wifi_scr(void)
{
    LV_IMG_DECLARE(wifi_qr_code);

    lv_obj_t* wifi_scr = lv_obj_create(NULL);

    lv_obj_t* exit_btn = lv_btn_create(wifi_scr);
    lv_obj_remove_style_all(exit_btn);
    lv_obj_set_size(exit_btn, 1, 1);
    lv_obj_set_align(exit_btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(exit_btn, app_exit_event_handler, LV_EVENT_LONG_PRESSED, NULL);

    lv_obj_t* wifi_wifi_img = lv_img_create(wifi_scr);
    lv_img_set_src(wifi_wifi_img, &wifi_qr_code);
    lv_obj_align(wifi_wifi_img, LV_ALIGN_CENTER, 0, 0);

    lv_scr_load_anim(wifi_scr, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}