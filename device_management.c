/*
 * device_management.c
 *
 *  Created on: 2019. 1. 28.
 *      Author: root
 */
#include "main.h"

static lv_indev_t* keyboard_indev;
static lv_indev_t* mouse_indev;

static void lv_design_set_mouse();
static void lv_design_set_monitor();
static void lv_design_set_keyboard();
lv_indev_t* lv_design_get_keyboard_device_ref();

lv_indev_t* lv_design_get_keyboard_device_ref()
{
	return keyboard_indev;
}

void lv_design_set_device();


static void lv_design_set_monitor()
{
    static lv_disp_buf_t disp_buf;
    static lv_color_t buf1_1[480*10];
    lv_disp_buf_init(&disp_buf, buf1_1, NULL, 480*10);
    monitor_init();
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.flush_cb = monitor_flush;    /*Used when `LV_VDB_SIZE != 0` in lv_conf.h (buffered drawing)*/
    disp_drv.buffer = &disp_buf;      /*Used when `LV_VDB_SIZE == 0` in lv_conf.h (unbuffered drawing)*/
//    disp_drv.disp_map = monitor_map;        /*Used when `LV_VDB_SIZE == 0` in lv_conf.h (unbuffered drawing)*/
    lv_disp_drv_register(&disp_drv);
}

static void lv_design_set_mouse()
{
    mouse_init();
    lv_indev_drv_t mouse_drv;
    lv_indev_drv_init(&mouse_drv);          /*Basic initialization*/
    mouse_drv.type = LV_INDEV_TYPE_POINTER;
    mouse_drv.read_cb = mouse_read;         /*This function will be called periodically (by the library) to get the mouse position and state*/
    mouse_indev = lv_indev_drv_register(&mouse_drv);
    LV_IMG_DECLARE(mouse_cursor_icon);                          /*Declare the image file.*/
    lv_obj_t * cursor_obj =  lv_img_create(lv_scr_act(), NULL); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);             /*Set the image source*/
    lv_indev_set_cursor(mouse_indev, cursor_obj);               /*Connect the image  object to the driver*/
}

static void lv_design_set_keyboard()
{
    keyboard_init();
    lv_indev_drv_t keyboard_drv;
    lv_indev_drv_init(&keyboard_drv);          /*Basic initialization*/
    keyboard_drv.type = LV_INDEV_TYPE_KEYPAD;
    keyboard_drv.read_cb = keyboard_read;         /*This function will be called periodically (by the library) to get the mouse position and state*/
    keyboard_indev = lv_indev_drv_register(&keyboard_drv);
}

void lv_design_set_device()
{
    lv_design_set_monitor();
    lv_design_set_mouse();
    lv_design_set_keyboard();
}

