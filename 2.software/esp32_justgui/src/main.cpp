#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "sd_card.h"
#include "lv_port_indev.h"
#include "lv_port_fatfs.h"
#include "display.h"
#include "sence_1.h"
#include "lv_page_common.h"

// #include "lv_home_page.h"
// #include "lv_scroll_page.h"
// #include "lv_weather_page.h"
// #include "lv_class_page.h"
// #include "lv_pc_state_page.h"
// #include "lv_wifi_page.h"
// #include "lv_brightness_page.h"

SdCard tf;
Display screen;

void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */

    screen.init();
    screen.setBackLight(0.5);
    lv_port_indev_init();

    // tf.init();
    // lv_fs_if_init();   

    lv_app_load_home_scr();
    // lv_app_scroll();
    // lv_app_load_weather_scr();
    // lv_app_load_class_scr();
    // lv_app_load_pc_state_scr();
    // lv_app_load_wifi_scr();
    // lv_app_load_light_scr();
}

void loop()
{
    screen.routine(); /* let the GUI do its work */
    delay(5);
}
