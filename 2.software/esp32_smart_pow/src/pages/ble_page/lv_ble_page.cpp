#include "lv_page_common.h"
#include <BleKeyboard.h>
#include <Arduino.h>

BleKeyboard blekeyboard;

static void press_prev_cb(lv_event_t* e)
{
    blekeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);

}
static void press_next_cb(lv_event_t* e)
{
    blekeyboard.write(KEY_MEDIA_NEXT_TRACK);

}

static void press_play_pause_cb(lv_event_t* e)
{
    blekeyboard.write(KEY_MEDIA_PLAY_PAUSE);

}

static void press_volume_up_cb(lv_event_t* e)
{
    blekeyboard.write(KEY_MEDIA_VOLUME_UP);

}

static void press_volume_down_cb(lv_event_t* e)
{
    blekeyboard.write(KEY_MEDIA_VOLUME_DOWN);

}

static void press_page_up_cb(lv_event_t* e)
{
    blekeyboard.write(KEY_PAGE_UP);

}

static void press_page_down_cb(lv_event_t* e)
{
    blekeyboard.write(KEY_PAGE_DOWN);

}

static void press_exit_cb(lv_event_t* e)
{
    //blekeyboard.end();
}

void lv_app_load_ble_scr(void)
{
    static lv_coord_t col_dsc[] = { 60, 60, 60, LV_GRID_TEMPLATE_LAST };
    static lv_coord_t row_dsc[] = { 60, 60, 60, LV_GRID_TEMPLATE_LAST };

    static uint8_t ble_flag=0;

    /*Create a container with grid*/
    lv_obj_t* ble_scr = lv_obj_create(NULL);
    lv_obj_t* cont = lv_obj_create(ble_scr);
    lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
    lv_obj_set_size(cont, 230, 230);
    lv_obj_center(cont);
    lv_obj_set_layout(cont, LV_LAYOUT_GRID);

    lv_obj_t* label;
    lv_obj_t* btn;

    btn = lv_btn_create(cont);
    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, 0,1,LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_add_event_cb(btn, press_prev_cb, LV_EVENT_PRESSED, NULL);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_PREV);
    lv_obj_center(label);

    btn = lv_btn_create(cont);
    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_add_event_cb(btn, press_play_pause_cb, LV_EVENT_PRESSED, NULL);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_PLAY);
    lv_obj_center(label);

    btn = lv_btn_create(cont);
    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, 2, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_add_event_cb(btn, press_next_cb, LV_EVENT_PRESSED, NULL);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_NEXT);
    lv_obj_center(label);

    btn = lv_btn_create(cont);
    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    lv_obj_add_event_cb(btn, press_volume_down_cb, LV_EVENT_PRESSED, NULL);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_VOLUME_MID);
    lv_obj_center(label);

    btn = lv_btn_create(cont);
    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    lv_obj_add_event_cb(btn, press_play_pause_cb, LV_EVENT_PRESSED, NULL);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_PAUSE);
    lv_obj_center(label);

    btn = lv_btn_create(cont);
    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, 2, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    lv_obj_add_event_cb(btn, press_volume_up_cb, LV_EVENT_PRESSED, NULL);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_VOLUME_MAX);
    lv_obj_center(label);

    btn = lv_btn_create(cont);
    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
    lv_obj_add_event_cb(btn, press_page_up_cb, LV_EVENT_PRESSED, NULL);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_LEFT);
    lv_obj_center(label);

    btn = lv_btn_create(cont);
    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
    lv_obj_add_event_cb(btn, press_page_down_cb, LV_EVENT_PRESSED, NULL);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_RIGHT);
    lv_obj_center(label);

    btn = lv_btn_create(cont);
    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, 2, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
    lv_obj_add_event_cb(btn, app_exit_event_handler, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(btn, press_exit_cb, LV_EVENT_LONG_PRESSED, NULL);
    label = lv_label_create(btn);
    lv_label_set_text(label, LV_SYMBOL_NEW_LINE);
    lv_obj_center(label);
    
    lv_scr_load_anim(ble_scr, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);

    if(ble_flag==0)
    {
        blekeyboard.begin();
        ble_flag=1;
    }

    
}