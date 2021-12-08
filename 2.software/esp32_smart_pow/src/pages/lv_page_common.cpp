#include "lv_page_common.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include <iostream>

const char *host = "api.seniverse.com";
/*privateKey改成自己的*/
const char *privateKey = "XXXXXXXXXX"; 
const char *city = "wuhan";
const char *language = "zh-Hans";

lv_user_weather_info_t user_weather_info = {0};

void app_exit_event_handler(lv_event_t* e)
{
    lv_app_scroll();
}

void lv_app_weather_update()
{
    WiFiClient client;
    DynamicJsonDocument Weather_Json(1400);

    if (!client.connect(host, 80))
    {
        Serial.println("Connect host failed!");
        return;
    }
    //Serial.println("host Conected!");

    String getUrl = "/v3/weather/daily.json?key=";
    getUrl += privateKey;
    getUrl += "&location=";
    getUrl += city;
    getUrl += "&language=";
    getUrl += language;
    client.print(String("GET ") + getUrl + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    //Serial.println("Get send");

    char endOfHeaders[] = "\r\n\r\n";
    bool ok = client.find(endOfHeaders);
    if (!ok)
    {
        Serial.println("No response or invalid response!");
    }
    //Serial.println("Skip headers");

    String line = "";

    line += client.readStringUntil('\n');

    //Serial.println(line);

    DeserializationError error = deserializeJson(Weather_Json, line);
    if (error)
    {
        Serial.println("deserialize json failed");
        return;
    }
    
    user_weather_info.day_one_text = Weather_Json["results"][0]["daily"][0]["text_day"].as<const int>();
    user_weather_info.day_one_temp_high = Weather_Json["results"][0]["daily"][0]["high"].as<const int>();
    user_weather_info.day_one_temp_low = Weather_Json["results"][0]["daily"][0]["low"].as<const int>();
    sscanf(Weather_Json["results"][0]["daily"][0]["date"].as<const char *>(),"%d-%d-%d",&user_weather_info.day_one_year,&user_weather_info.day_one_month,&user_weather_info.day_one_date);
    user_weather_info.day_one_humi = Weather_Json["results"][0]["daily"][0]["humidity"].as<const int>();
    user_weather_info.day_one_windspeed = Weather_Json["results"][0]["daily"][0]["wind_speed"].as<const int>();
    strcpy(user_weather_info.day_one_wind_direction,Weather_Json["results"][0]["daily"][0]["wind_direction"].as<const char *>());

    user_weather_info.day_two_text = Weather_Json["results"][0]["daily"][1]["text_day"].as<const int>();
    user_weather_info.day_two_temp_high = Weather_Json["results"][0]["daily"][1]["high"].as<const int>();
    user_weather_info.day_two_temp_low = Weather_Json["results"][0]["daily"][1]["low"].as<const int>();
    sscanf(Weather_Json["results"][0]["daily"][1]["date"].as<const char *>(),"%d-%d-%d",&user_weather_info.day_two_year,&user_weather_info.day_two_month,&user_weather_info.day_two_date);
    
    user_weather_info.day_three_text = Weather_Json["results"][0]["daily"][2]["text_day"].as<const int>();
    user_weather_info.day_three_temp_high = Weather_Json["results"][0]["daily"][2]["high"].as<const int>();
    user_weather_info.day_three_temp_low = Weather_Json["results"][0]["daily"][2]["low"].as<const int>();
    sscanf(Weather_Json["results"][0]["daily"][2]["date"].as<const char *>(),"%d-%d-%d",&user_weather_info.day_three_year,&user_weather_info.day_three_month,&user_weather_info.day_three_date);

    Weather_Json.clear();

    client.stop();
}