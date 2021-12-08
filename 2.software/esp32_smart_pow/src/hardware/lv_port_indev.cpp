/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include <Arduino.h>

#define KEY_RIGHT_PIN 5
#define KEY_LEFT_PIN 16
#define KEY_OK_PIN 17

static void keypad_init(void);
static void keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static lv_key_t key_value(void);

lv_indev_t *indev_encoder;

void lv_port_indev_init(void)
{
    /* Here you will find example implementation of input devices supported by LittelvGL:
	 *  - Touchpad
	 *  - Mouse (with cursor support)
	 *  - Keypad (supports GUI usage only with key)
	 *  - Encoder (supports GUI usage only with: left, right, push)
	 *  - Button (external buttons to press points on the screen)
	 *
	 *  The `..._read()` function are only examples.
	 *  You should shape them according to your hardware
	 */

    static lv_indev_drv_t indev_drv;

    /*------------------
	 * Encoder
	 * -----------------*/

    /*Initialize your encoder if you have*/
    keypad_init();

    lv_group_t * input_group = lv_group_create();
    lv_group_set_default(input_group);

    /*Register a encoder input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = keypad_read;
    indev_encoder = lv_indev_drv_register(&indev_drv);

    lv_indev_set_group(indev_encoder,input_group);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
  * Encoder
  * -----------------*/

/* Initialize your keypad */
static void keypad_init(void)
{
    /*Your code comes here*/
    pinMode(KEY_RIGHT_PIN, INPUT_PULLUP);
    pinMode(KEY_LEFT_PIN, INPUT_PULLUP);
    pinMode(KEY_OK_PIN, INPUT_PULLUP);
}

/* Will be called by the library to read the encoder */
static void keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    static uint32_t last_key = 0;
    uint32_t act_key = key_value();

    if(act_key!=0)
    {
        data->state = LV_INDEV_STATE_PRESSED;
        last_key = act_key;
    }
    else{
        data->state = LV_INDEV_STATE_RELEASED;
    }
    data->key = last_key;
}

static lv_key_t key_value(void)
{
    if (!digitalRead(KEY_RIGHT_PIN))
    {
        return LV_KEY_RIGHT;
    }
    if (!digitalRead(KEY_LEFT_PIN))
    {
        return LV_KEY_LEFT;
    }
    if (!digitalRead(KEY_OK_PIN))
    {
        return LV_KEY_ENTER;
    }
    return 0;
}