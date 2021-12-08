#include "lv_page_common.h"

static void class_item_create(lv_obj_t* parent_obj, lv_event_cb_t event_cb, lv_style_t* line_style)
{
    lv_obj_t* btn;
    lv_obj_t* label;

    btn = lv_btn_create(parent_obj);
    lv_obj_set_width(btn, lv_pct(98));
    lv_obj_set_height(btn, lv_pct(98));
    lv_obj_set_style_bg_color(btn, lv_color_white(), 0);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_LONG_PRESSED, NULL);
    label = lv_label_create(btn);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_recolor(label, true);
    lv_label_set_text(label, "#000000 1#");

    static lv_point_t line_1_points[] = { {-10,25}, {190,25} };
    lv_obj_t* line_1 = lv_line_create(btn);
    lv_line_set_points(line_1, line_1_points, 2);
    lv_obj_add_style(line_1, line_style, 0);

    static lv_point_t line_2_points[] = { {-10,60}, {190,60} };
    lv_obj_t* line_2 = lv_line_create(btn);
    lv_line_set_points(line_2, line_2_points, 2);
    lv_obj_add_style(line_2, line_style, 0);

    static lv_point_t line_3_points[] = { {-10,95}, {190,95} };
    lv_obj_t* line_3 = lv_line_create(btn);
    lv_line_set_points(line_3, line_3_points, 2);
    lv_obj_add_style(line_3, line_style, 0);

    static lv_point_t line_4_points[] = { {-10,130}, {190,130} };
    lv_obj_t* line_4 = lv_line_create(btn);
    lv_line_set_points(line_4, line_4_points, 2);
    lv_obj_add_style(line_4, line_style, 0);

    static lv_point_t line_5_points[] = { {-10,165}, {190,165} };
    lv_obj_t* line_5 = lv_line_create(btn);
    lv_line_set_points(line_5, line_5_points, 2);
    lv_obj_add_style(line_5, line_style, 0);

}

void lv_app_load_class_scr(void)
{
    lv_obj_t* class_scr = lv_obj_create(NULL);

    static lv_style_t font_16_label_style;
    lv_style_init(&font_16_label_style);
    lv_style_set_text_font(&font_16_label_style, &myfont_16);


    static lv_style_t line_style;
    lv_style_init(&line_style);
    lv_style_set_line_color(&line_style, lv_palette_main(LV_PALETTE_LIGHT_BLUE));
    lv_style_set_line_width(&line_style, 1);
    lv_style_set_line_opa(&line_style, 50);

    lv_obj_t* class_date_obj = lv_obj_create(class_scr);
    lv_obj_set_width(class_date_obj, 240);
    lv_obj_set_height(class_date_obj, 240);
    lv_obj_set_flex_flow(class_date_obj, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scrollbar_mode(class_date_obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_clip_corner(class_date_obj, true, 0);
    lv_obj_set_style_border_width(class_date_obj, 0, 0);
    lv_obj_set_scroll_dir(class_date_obj, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(class_date_obj, LV_SCROLL_SNAP_CENTER);

    class_item_create(class_date_obj, app_exit_event_handler, &line_style);
    class_item_create(class_date_obj, app_exit_event_handler, &line_style);
    class_item_create(class_date_obj, app_exit_event_handler, &line_style);
    class_item_create(class_date_obj, app_exit_event_handler, &line_style);
    class_item_create(class_date_obj, app_exit_event_handler, &line_style);

    lv_event_send(class_date_obj, LV_EVENT_SCROLL, NULL);
    lv_obj_scroll_to_view(lv_obj_get_child(class_date_obj, 0), LV_ANIM_ON);

    lv_scr_load_anim(class_scr, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}