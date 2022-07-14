/*
 * drv_indev.c
 *
 *  Created on: 2022Äê5ÔÂ14ÈÕ
 *      Author: dreamcmi
 */


/**
 * @file lv_hal_indev.c
 *
 * @description Input device HAL interface
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "ch32v30x.h"
#include "drv_indev.h"

static void keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1) == 0) {
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_KEY_UP;
    } else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == 0) {
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_KEY_DOWN;
    } else if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6) == 0) {
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_KEY_LEFT;
    } else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == 0) {
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_KEY_RIGHT;
    } else if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13) == 0) {
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_KEY_ENTER;
    } else {
    }
}

void lv_port_indev_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_13;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    static lv_indev_drv_t indev_drv;
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);
}

