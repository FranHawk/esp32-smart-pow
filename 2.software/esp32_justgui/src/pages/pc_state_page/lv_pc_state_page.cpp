#include "lv_page_common.h"

static void pc_state_set_angle(void* obj, int32_t v)
{
    lv_arc_set_value((lv_obj_t*)obj, v);
}

static void pc_usage_arc_value_change_cb(lv_event_t* e)
{
    lv_obj_t* arc = lv_event_get_target(e);
    lv_obj_t* label = (lv_obj_t*)lv_event_get_user_data(e);

    lv_label_set_text_fmt(label, "CPU %d%%", lv_arc_get_value(arc));
    lv_obj_align_to(label, arc, LV_ALIGN_CENTER, 0, 0);
}

static void ram_usage_arc_value_change_cb(lv_event_t* e)
{
    lv_obj_t* arc = lv_event_get_target(e);
    lv_obj_t* label = (lv_obj_t*)lv_event_get_user_data(e);

    lv_label_set_text_fmt(label, "RAM %d%%", lv_arc_get_value(arc));
    lv_obj_align_to(label, arc, LV_ALIGN_CENTER, 0, 0);
}

void lv_app_load_pc_state_scr(void)
{

    lv_obj_t* pc_state_scr = lv_obj_create(NULL);

    lv_obj_t* exit_btn = lv_btn_create(pc_state_scr);
    lv_obj_remove_style_all(exit_btn);
    lv_obj_set_size(exit_btn, 1, 1);
    lv_obj_set_align(exit_btn, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_event_cb(exit_btn, app_exit_event_handler, LV_EVENT_LONG_PRESSED, NULL);

    lv_obj_t* pc_usage_arc = lv_arc_create(pc_state_scr);
    lv_obj_t* pc_usage_label = lv_label_create(pc_usage_arc);

    lv_obj_set_size(pc_usage_arc, 100, 100);
    lv_arc_set_rotation(pc_usage_arc, 270);
    lv_arc_set_bg_angles(pc_usage_arc, 0, 360);
    lv_obj_remove_style(pc_usage_arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(pc_usage_arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_align(pc_usage_arc, LV_ALIGN_TOP_LEFT,10,10);
    lv_obj_add_event_cb(pc_usage_arc, pc_usage_arc_value_change_cb, LV_EVENT_ALL, pc_usage_label);
     
    lv_label_set_text(pc_usage_label, "CPU 0%");
    lv_obj_align(pc_usage_label, LV_ALIGN_CENTER, 0, 0);

    lv_anim_t pc_usage_arc_anim;
    lv_anim_init(&pc_usage_arc_anim);
    lv_anim_set_var(&pc_usage_arc_anim, pc_usage_arc);
    lv_anim_set_exec_cb(&pc_usage_arc_anim, pc_state_set_angle);
    lv_anim_set_time(&pc_usage_arc_anim, 500);
    lv_anim_set_values(&pc_usage_arc_anim, 0, 80);
    lv_anim_start(&pc_usage_arc_anim);

    lv_obj_t* ram_usage_arc = lv_arc_create(pc_state_scr);
    lv_obj_t* ram_usage_label = lv_label_create(ram_usage_arc);

    lv_obj_set_size(ram_usage_arc, 100, 100);
    lv_arc_set_rotation(ram_usage_arc, 270);
    lv_arc_set_bg_angles(ram_usage_arc, 0, 360);
    lv_obj_remove_style(ram_usage_arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(ram_usage_arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_align(ram_usage_arc, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_add_event_cb(ram_usage_arc, ram_usage_arc_value_change_cb, LV_EVENT_ALL, ram_usage_label);

    lv_label_set_text(ram_usage_label, "RAM 0%");
    lv_obj_align(ram_usage_label, LV_ALIGN_CENTER, 0, 0);

    lv_anim_t ram_usage_arc_anim;
    lv_anim_init(&ram_usage_arc_anim);
    lv_anim_set_var(&ram_usage_arc_anim, ram_usage_arc);
    lv_anim_set_exec_cb(&ram_usage_arc_anim, pc_state_set_angle);
    lv_anim_set_values(&ram_usage_arc_anim, 0, 50);
    lv_anim_start(&ram_usage_arc_anim);

    lv_obj_t* cpu_title_label = lv_label_create(pc_state_scr);
    lv_label_set_text(cpu_title_label, "CPU");
    lv_obj_align(cpu_title_label, LV_ALIGN_LEFT_MID, 40, 10);

    lv_obj_t* cpu_temp_label = lv_label_create(pc_state_scr);
    lv_label_set_text(cpu_temp_label, "TEMP 40°C");
    lv_obj_align(cpu_temp_label, LV_ALIGN_LEFT_MID, 20, 25);

    lv_obj_t* cpu_freq_label = lv_label_create(pc_state_scr);
    lv_label_set_text(cpu_freq_label, "FREQ 1.25GHz");
    lv_obj_align(cpu_freq_label, LV_ALIGN_LEFT_MID, 20, 40);

    lv_obj_t* ram_title_label = lv_label_create(pc_state_scr);
    lv_label_set_text(ram_title_label, "RAM");
    lv_obj_align(ram_title_label, LV_ALIGN_RIGHT_MID, -40, 10);

    lv_obj_t* ram_used_label = lv_label_create(pc_state_scr);
    lv_label_set_text(ram_used_label, "USED 3.4G");
    lv_obj_align(ram_used_label, LV_ALIGN_RIGHT_MID, -20, 25);

    lv_obj_t* ram_avaliable_label = lv_label_create(pc_state_scr);
    lv_label_set_text(ram_avaliable_label, "AVAL 4.7G");
    lv_obj_align(ram_avaliable_label, LV_ALIGN_RIGHT_MID, -20, 40);

    lv_obj_t* gpu_title_label = lv_label_create(pc_state_scr);
    lv_label_set_text(gpu_title_label, "GPU");
    lv_obj_align(gpu_title_label, LV_ALIGN_BOTTOM_LEFT, 40, -45);

    lv_obj_t* vram_used_label = lv_label_create(pc_state_scr);
    lv_label_set_text(vram_used_label, "VRAM 1.5G/4G");
    lv_obj_align(vram_used_label, LV_ALIGN_BOTTOM_LEFT,  20, -30);

    lv_obj_t* gpu_freq_label = lv_label_create(pc_state_scr);
    lv_label_set_text(gpu_freq_label, "FREQ 1.25GHz");
    lv_obj_align(gpu_freq_label, LV_ALIGN_BOTTOM_LEFT, 20, -15);

    lv_obj_t* fps_label = lv_label_create(pc_state_scr);
    lv_label_set_text(fps_label, "FPS 60");
    lv_obj_align(fps_label, LV_ALIGN_BOTTOM_RIGHT, -40, -45);

    lv_obj_t* upload_label = lv_label_create(pc_state_scr);
    lv_label_set_text(upload_label,LV_SYMBOL_UP " 1024MB/s");
    lv_obj_align(upload_label, LV_ALIGN_BOTTOM_LEFT, 140, -30);

    lv_obj_t* download_label = lv_label_create(pc_state_scr);
    lv_label_set_text(download_label,LV_SYMBOL_DOWN " 2048MB/s");
    lv_obj_align(download_label, LV_ALIGN_BOTTOM_LEFT, 140, -15);

    lv_scr_load_anim(pc_state_scr, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}