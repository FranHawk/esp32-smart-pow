#include "lv_page_common.h"
#include <WiFi.h>

lv_timer_t *timer_pcstate;

static const char *host = "192.168.1.101";

static void lv_pc_state_update(lv_obj_t* pc_state_scr)
{
    WiFiClient client;

    if (!client.connect(host, 80,200))
    {
        Serial.println("Connect host failed!");
        return;
    }

    String getUrl = "/sse";
    client.print(String("GET ") + getUrl + " HTTP/1.1\r\n" + "Content-Type=application/json;charset=utf-8\r\n" + "Host: " + host + "\r\n" + "User-Agent=ESP32\r\n" + "Connection: close\r\n\r\n");
    Serial.println("Get send");

    delay(10);

    char endOfHeaders[] = "\n\n";
    bool ok = client.find(endOfHeaders);
    if (!ok)
    {
        Serial.println("No response or invalid response!");
    }
    Serial.println("here");
    String line = "";

    line += client.readStringUntil('\n');

    Serial.println(line);

    int16_t dataStart = 0;
    int16_t dataEnd = 0;
    String dataStr;

    lv_obj_t* pc_usage_arc = lv_obj_get_child(pc_state_scr,1);
    char cpuUsage[] = "CPU Usage";
    dataStart = line.indexOf(cpuUsage) + strlen(cpuUsage);
    dataEnd = line.indexOf("%", dataStart);
    dataStr = line.substring(dataStart, dataEnd);
    lv_arc_set_value(pc_usage_arc,dataStr.toInt());

    Serial.println("here1");

    lv_obj_t* ram_usage_arc = lv_obj_get_child(pc_state_scr,2);
    char ramUsage[] = "RAM Usage";
    dataStart = line.indexOf(ramUsage) + strlen(ramUsage);
    dataEnd = line.indexOf("%", dataStart);
    dataStr = line.substring(dataStart, dataEnd);
    lv_arc_set_value(ram_usage_arc,dataStr.toInt());

    Serial.println(dataStr.toInt());

    lv_obj_t* cpu_temp_label = lv_obj_get_child(pc_state_scr,4);
    char cpuTemp[] = "CPU Temp";
    dataStart = line.indexOf(cpuTemp) + strlen(cpuTemp);
    dataEnd = line.indexOf("c", dataStart);
    dataStr = line.substring(dataStart, dataEnd);
    lv_label_set_text_fmt(cpu_temp_label, "TEMP %s°C",dataStr.c_str());

    Serial.println("here3");

    lv_obj_t* cpu_freq_label = lv_obj_get_child(pc_state_scr,5);
    char cpuFreq[] = "CPU Frequency";
    dataStart = line.indexOf(cpuFreq) + strlen(cpuFreq);
    dataEnd = line.indexOf("GHz", dataStart);
    dataStr = line.substring(dataStart, dataEnd);
    lv_label_set_text_fmt(cpu_freq_label, "FREQ %sGHz",dataStr.c_str());

    Serial.println("here4");

    lv_obj_t* ram_used_label = lv_obj_get_child(pc_state_scr,7);
    char ramUsed[] = "RAM Used";
    dataStart = line.indexOf(ramUsed) + strlen(ramUsed);
    dataEnd = line.indexOf("GB", dataStart);
    dataStr = line.substring(dataStart, dataEnd);
    lv_label_set_text_fmt(ram_used_label, "USED %sG",dataStr.c_str());

    Serial.println("here5");

    lv_obj_t* ram_avaliable_label = lv_obj_get_child(pc_state_scr,8);
    char ramAvail[] = "RAM Aval";
    dataStart = line.indexOf(ramAvail) + strlen(ramAvail);
    dataEnd = line.indexOf("GB", dataStart);
    dataStr = line.substring(dataStart, dataEnd);
    lv_label_set_text_fmt(ram_avaliable_label, "AVAL %sG",dataStr.c_str());

    Serial.println("here6");

    lv_obj_t* vram_used_label = lv_obj_get_child(pc_state_scr,10);
    char gpuUsed[] = "GPU Used";
    dataStart = line.indexOf(gpuUsed) + strlen(gpuUsed);
    dataEnd = line.indexOf("GB", dataStart);
    dataStr = line.substring(dataStart, dataEnd);
    lv_label_set_text_fmt(vram_used_label, "VRAM %sG/4G",dataStr.c_str());

    Serial.println("here7");

    lv_obj_t* gpu_freq_label = lv_obj_get_child(pc_state_scr,11);
    char gpuFreq[] = "GPU Frequency";
    dataStart = line.indexOf(gpuFreq) + strlen(gpuFreq);
    dataEnd = line.indexOf("GHz", dataStart);
    dataStr = line.substring(dataStart, dataEnd);
    lv_label_set_text_fmt(gpu_freq_label, "FREQ %sGHz",dataStr.c_str());

    Serial.println("here8");

    lv_obj_t* fps_label = lv_obj_get_child(pc_state_scr,12);
    char fps[] = "FPS";
    dataStart = line.indexOf(fps) + strlen(fps);
    dataEnd = line.indexOf("Hz", dataStart);
    dataStr = line.substring(dataStart, dataEnd);
    lv_label_set_text_fmt(fps_label, "FPS %s",dataStr.c_str());

    Serial.println("here9");

    lv_obj_t* upload_label = lv_obj_get_child(pc_state_scr,13);
    Serial.println("here11");
    char upload[] = "UPLOAD ";
    dataStart = line.indexOf(upload) + strlen(upload);
    dataEnd = line.indexOf("MB/s", dataStart);
    dataStr = line.substring(dataStart, dataEnd);
    Serial.println("here12");
    Serial.println(dataStr.c_str());
    lv_label_set_text_fmt(upload_label,"> %sMB/s",dataStr.c_str());

    Serial.println("here10");

    lv_obj_t* download_label = lv_obj_get_child(pc_state_scr,14);
    char download[] = "DOWNLOAD ";
    dataStart = line.indexOf(download) + strlen(download);
    dataEnd = line.indexOf("MB/s", dataStart);
    dataStr = line.substring(dataStart, dataEnd);
    lv_label_set_text_fmt(download_label,"< %sMB/s",dataStr.c_str());

    client.stop();
}

static void lv_timer_time_update(lv_timer_t *timer)
{
    Serial.println("hello");
    if (timer->user_data != NULL)
    {
        lv_obj_t *pc_state_scr = (lv_obj_t *)timer->user_data;
        lv_pc_state_update(pc_state_scr);
    }
}

static void lv_timer_time_stop(void)
{
    Serial.println("time");
    lv_timer_del(timer_pcstate);
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
    lv_obj_add_event_cb(exit_btn, (lv_event_cb_t)lv_timer_time_stop, LV_EVENT_LONG_PRESSED, NULL);

    lv_obj_t* pc_usage_arc = lv_arc_create(pc_state_scr);
    lv_obj_t* pc_usage_label = lv_label_create(pc_usage_arc);

    lv_obj_set_size(pc_usage_arc, 100, 100);
    lv_arc_set_rotation(pc_usage_arc, 270);
    lv_arc_set_bg_angles(pc_usage_arc, 0, 360);
    lv_obj_remove_style(pc_usage_arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(pc_usage_arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_align(pc_usage_arc, LV_ALIGN_TOP_LEFT,10,10);
    lv_obj_add_event_cb(pc_usage_arc, pc_usage_arc_value_change_cb, LV_EVENT_ALL, pc_usage_label);
    lv_arc_set_value(pc_usage_arc,0);

    lv_label_set_text(pc_usage_label, "CPU 0%");
    lv_obj_align(pc_usage_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* ram_usage_arc = lv_arc_create(pc_state_scr);
    lv_obj_t* ram_usage_label = lv_label_create(ram_usage_arc);

    lv_obj_set_size(ram_usage_arc, 100, 100);
    lv_arc_set_rotation(ram_usage_arc, 270);
    lv_arc_set_bg_angles(ram_usage_arc, 0, 360);
    lv_obj_remove_style(ram_usage_arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(ram_usage_arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_align(ram_usage_arc, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_add_event_cb(ram_usage_arc, ram_usage_arc_value_change_cb, LV_EVENT_ALL, ram_usage_label);
    lv_arc_set_value(ram_usage_arc,0);

    lv_label_set_text(ram_usage_label, "RAM 0%");
    lv_obj_align(ram_usage_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* cpu_title_label = lv_label_create(pc_state_scr);
    lv_label_set_text(cpu_title_label, "CPU");
    lv_obj_align(cpu_title_label, LV_ALIGN_LEFT_MID, 40, 10);

    lv_obj_t* cpu_temp_label = lv_label_create(pc_state_scr);
    lv_label_set_text(cpu_temp_label, "TEMP 0°C");
    lv_obj_align(cpu_temp_label, LV_ALIGN_LEFT_MID, 20, 25);

    lv_obj_t* cpu_freq_label = lv_label_create(pc_state_scr);
    lv_label_set_text(cpu_freq_label, "FREQ 0GHz");
    lv_obj_align(cpu_freq_label, LV_ALIGN_LEFT_MID, 20, 40);

    lv_obj_t* ram_title_label = lv_label_create(pc_state_scr);
    lv_label_set_text(ram_title_label, "RAM");
    lv_obj_align(ram_title_label, LV_ALIGN_RIGHT_MID, -40, 10);

    lv_obj_t* ram_used_label = lv_label_create(pc_state_scr);
    lv_label_set_text(ram_used_label, "USED 0G");
    lv_obj_align(ram_used_label, LV_ALIGN_RIGHT_MID, -20, 25);

    lv_obj_t* ram_avaliable_label = lv_label_create(pc_state_scr);
    lv_label_set_text(ram_avaliable_label, "AVAL 0G");
    lv_obj_align(ram_avaliable_label, LV_ALIGN_RIGHT_MID, -20, 40);

    lv_obj_t* gpu_title_label = lv_label_create(pc_state_scr);
    lv_label_set_text(gpu_title_label, "GPU");
    lv_obj_align(gpu_title_label, LV_ALIGN_BOTTOM_LEFT, 40, -45);

    lv_obj_t* vram_used_label = lv_label_create(pc_state_scr);
    lv_label_set_text(vram_used_label, "VRAM 0G/4G");
    lv_obj_align(vram_used_label, LV_ALIGN_BOTTOM_LEFT,  20, -30);

    lv_obj_t* gpu_freq_label = lv_label_create(pc_state_scr);
    lv_label_set_text(gpu_freq_label, "FREQ 0GHz");
    lv_obj_align(gpu_freq_label, LV_ALIGN_BOTTOM_LEFT, 20, -15);

    lv_obj_t* fps_label = lv_label_create(pc_state_scr);
    lv_label_set_text(fps_label, "FPS 0");
    lv_obj_align(fps_label, LV_ALIGN_BOTTOM_RIGHT, -40, -45);

    lv_obj_t* upload_label = lv_label_create(pc_state_scr);
    lv_label_set_text(upload_label,"> 0.0MB/s");
    lv_obj_align(upload_label, LV_ALIGN_BOTTOM_LEFT, 140, -30);

    lv_obj_t* download_label = lv_label_create(pc_state_scr);
    lv_label_set_text(download_label,"< 0MB/s");
    lv_obj_align(download_label, LV_ALIGN_BOTTOM_LEFT, 140, -15);

    lv_scr_load_anim(pc_state_scr, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);

    timer_pcstate = lv_timer_create(lv_timer_time_update, 1000, pc_state_scr);
}