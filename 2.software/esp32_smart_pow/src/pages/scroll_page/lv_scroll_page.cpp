#include "lv_page_common.h"

typedef void(*lv_app_load_fp)(void);

static void event_handler(lv_event_t* e)
{
    lv_app_load_fp fp;
    lv_event_code_t code = lv_event_get_code(e);
    
    if (code == LV_EVENT_LONG_PRESSED) {
        
        //LV_LOG_USER("Clicked");
        fp = (lv_app_load_fp)lv_event_get_user_data(e);
        //LV_LOG_USER("Clicked2");
        if (fp != NULL)
        {
            //LV_LOG_USER("Clicked3");
            (*fp)();
        }
    }
}

static void menu_item_create(lv_obj_t* parent_obj,lv_style_t* label_style,lv_event_cb_t event_cb,const void* img_src,const char* text,lv_app_load_fp lv_app_scr_load)
{
    lv_obj_t* btn = lv_btn_create(parent_obj);
    lv_obj_remove_style_all(btn);
    lv_obj_set_width(btn, lv_pct(100));
    lv_obj_set_height(btn, lv_pct(100));
    lv_obj_set_style_bg_color(btn, lv_color_white(), 0);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_ALL, (void *)lv_app_scr_load);

    lv_obj_t* img;
    lv_obj_t* label;

    img = lv_img_create(btn);
    lv_img_set_src(img, img_src);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    label = lv_label_create(btn);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_label_set_recolor(label, true);
    lv_obj_add_style(label, label_style, 0);
    lv_label_set_text(label, text);
}

static void scroll_event_cb(lv_event_t* e)
{
    
    lv_obj_t* cont = lv_event_get_target(e);

    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_x_center = cont_a.x1 + lv_area_get_width(&cont_a) / 2;

    lv_coord_t r = lv_obj_get_width(cont) * 5 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for (i = 0; i < child_cnt; i++) {
        lv_obj_t* child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);
        lv_coord_t child_x_center = child_a.x1 + lv_area_get_width(&child_a) / 2;

        lv_coord_t diff_x = child_x_center - cont_x_center;
        diff_x = LV_ABS(diff_x);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t y;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if (diff_x >= r) {
            y = r;
        }
        else {
            /*Use Pythagoras theorem to get x from radius and y*/
            lv_coord_t y_sqr = r * r - diff_x * diff_x;
            lv_sqrt_res_t res;
            lv_sqrt(y_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            y = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_y(child, y, 0);
    }
}

void lv_app_scroll(void)
{
    LV_IMG_DECLARE(alert);
    LV_IMG_DECLARE(authority);
    LV_IMG_DECLARE(cloud);
    LV_IMG_DECLARE(copy);
    LV_IMG_DECLARE(observation);
    LV_IMG_DECLARE(pending);
    LV_IMG_DECLARE(wireless);
    LV_IMG_DECLARE(ble);

    static lv_style_t label_style;

    //lv_obj_t* cont = lv_obj_create(lv_scr_act());
    lv_obj_t* cont = lv_obj_create(NULL);
    lv_obj_remove_style_all(cont);



    lv_obj_set_style_bg_color(cont, lv_color_white(), 0);
    lv_obj_set_size(cont, 240, 240);
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);
    //lv_obj_set_style_radius(cont, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(cont, true, 0);
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_set_scroll_dir(cont, LV_DIR_HOR);
    lv_obj_set_scroll_snap_x(cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    lv_style_init(&label_style);
    lv_style_set_text_font(&label_style, &myfont);

    menu_item_create(cont, &label_style, event_handler, &copy, "#000000 扩展功能#", NULL);
    menu_item_create(cont, &label_style, event_handler, &ble, "#000000 蓝牙键盘#", lv_app_load_ble_scr);
    menu_item_create(cont, &label_style, event_handler, &alert, "#000000 屏幕亮度#", lv_app_load_light_scr);
    menu_item_create(cont, &label_style, event_handler, &wireless, "#000000 无线配网#", lv_app_load_wifi_scr);
    menu_item_create(cont, &label_style, event_handler, &observation, "#000000 电脑性能#", lv_app_load_pc_state_scr);
    menu_item_create(cont, &label_style, event_handler, &pending, "#000000 课程表#", lv_app_load_class_scr);
    menu_item_create(cont, &label_style, event_handler, &cloud, "#000000 天气#", lv_app_load_weather_scr);
    menu_item_create(cont, &label_style, event_handler, &authority, "#000000 时钟#",lv_app_load_home_scr);

    lv_obj_scroll_to_view(lv_obj_get_child(cont, 7), LV_ANIM_OFF);

    lv_scr_load_anim(cont, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 400, 0, true);    

}
