#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "sd_card.h"
#include "lv_port_indev.h"
#include "lv_port_fatfs.h"
#include "display.h"
#include "lv_page_common.h"

#include <WiFi.h>
#include <time.h>

const char *ssid = "master";
const char *password = "guojiwutai";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 8*3600; 
const int   daylightOffset_sec = 8*3600;

SdCard tf;
Display screen;

float g_screen_brightness = 0.4;

void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    lv_app_weather_update();
    
     
    screen.init();
    screen.setBackLight(g_screen_brightness);
    
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


