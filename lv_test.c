/**
 * @file lv_test_group.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "stdio.h"
#include "main.h"
#include "lv_ex_conf.h"
//#include "lv_test_group.h"
#define USE_LV_GROUP 1

#define USE_LV_TESTS 1
#if USE_LV_GROUP && USE_LV_TESTS

#include "lvgl/lv_hal/lv_hal_indev.h"

#if LV_EX_KEYBOARD || LV_EX_MOUSEWHEEL
#include "lv_drv_conf.h"
#endif

#if LV_EX_KEYBOARD
#include "lv_drivers/indev/keyboard.h"
#endif

#if LV_EX_MOUSEWHEEL
#include "lv_drivers/indev/mousewheel.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
#if 0
/**********************
 *  STATIC PROTOTYPES
 **********************/
/*To emulate some keys on the window header*/
static bool win_btn_read(lv_indev_data_t * data);
static lv_res_t win_btn_press(lv_obj_t * btn);
static lv_res_t win_btn_click(lv_obj_t * btn);

static void group_focus_cb(lv_group_t * group);

/*Dummy action functions*/
static lv_res_t press_action(lv_obj_t * btn);
static lv_res_t select_action(lv_obj_t * btn);
static lv_res_t change_action(lv_obj_t * btn);
static lv_res_t click_action(lv_obj_t * btn);
static lv_res_t long_press_action(lv_obj_t * btn);

/**********************
 *  STATIC VARIABLES
 **********************/
static uint32_t last_key;
static lv_indev_state_t last_key_state = LV_INDEV_STATE_REL;
static lv_group_t * g;
static lv_obj_t * win;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/


bool ta_chk(lv_obj_t * ta, uint32_t c)
{
    static bool run;

    /*Prevent to be called from every `lv_ta_add_char`*/
    if(run) return true;

    run = true;

    lv_ta_add_char(ta, c);
    lv_ta_add_char(ta, '.');

    run = false;
    return false;
}

/**
 * Create base groups to test their functionalities
 */
void lv_test(void)
{
    g = lv_group_create();
   // lv_group_set_focus_cb(g, group_focus_cb);


#if LV_EX_KEYBOARD
    lv_indev_drv_t rael_kb_drv;
    rael_kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    rael_kb_drv.read = keyboard_read;
    lv_indev_t * real_kb_indev = lv_indev_drv_register(&rael_kb_drv);
    lv_indev_set_group(real_kb_indev, g);
#endif

#if LV_EX_MOUSEWHEEL
    lv_indev_drv_t enc_drv;
    enc_drv.type = LV_INDEV_TYPE_ENCODER;
    enc_drv.read = mousewheel_read;
    lv_indev_t * enc_indev = lv_indev_drv_register(&enc_drv);
    lv_indev_set_group(enc_indev, g);
#endif

    win = lv_obj_create(lv_scr_act(), NULL);
    /*Create a window to hold all the objects*/
/*    static lv_style_t win_style;
    lv_style_copy(&win_style, &lv_style_transp);
    win_style.body.padding.hor = LV_DPI / 4;
    win_style.body.padding.ver = LV_DPI / 4;
    win_style.body.padding.inner = LV_DPI / 4;

    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Group test");
    lv_page_set_scrl_layout(lv_win_get_content(win), LV_LAYOUT_PRETTY);
    lv_win_set_style(win, LV_WIN_STYLE_CONTENT_SCRL, &win_style);
    lv_group_add_obj(g, lv_win_get_content(win));
*/
    lv_obj_t * ta = lv_ta_create(win, NULL);
    lv_ta_set_cursor_type(ta, LV_CURSOR_BLOCK);
    lv_group_add_obj(g, ta);


//    lv_group_focus_obj(lv_group_get_focused(g));
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Read function for the input device which emulates keys on the window header
 * @param data store the last key and its staee here
 * @return false because the reading in not buffered
 */
static bool win_btn_read(lv_indev_data_t * data)
{
    data->state = last_key_state;
    data->key = last_key;


    return false;
}

/**
 * Called when a control button on the window header is pressed to change the key state to PRESSED
 * @param btn pointer t to a button on the window header
 * @return LV_RES_OK  because the button is not deleted
 */
static lv_res_t win_btn_press(lv_obj_t * btn)
{
    LV_OBJ_FREE_NUM_TYPE c = lv_obj_get_free_num(btn);
    last_key_state = LV_INDEV_STATE_PR;
    last_key = c;

    return LV_RES_OK;
}

/**
 * Called when a control button on the window header is released to change the key state to RELEASED
 * @param btn pointer t to a button on the window header
 * @return LV_RES_OK  because the button is not deleted
 */
static lv_res_t win_btn_click(lv_obj_t * btn)
{
    (void) btn; /*Unused*/
    last_key_state = LV_INDEV_STATE_REL;

    return LV_RES_OK;
}


static void group_focus_cb(lv_group_t * group)
{
    lv_obj_t * f = lv_group_get_focused(group);
    if(f != win) lv_win_focus(win, f, 200);
}

/*
 * Dummy action functions
 */

static lv_res_t press_action(lv_obj_t * btn)
{
    (void) btn; /*Unused*/

#if LV_EX_PRINTF
    printf("Press\n");
#endif
    return LV_RES_OK;
}

static lv_res_t select_action(lv_obj_t * btn)
{
    (void) btn; /*Unused*/

#if LV_EX_PRINTF
    printf("Select\n");
#endif
    return LV_RES_OK;
}

static lv_res_t change_action(lv_obj_t * btn)
{
    (void) btn; /*Unused*/

#if LV_EX_PRINTF
    printf("Change\n");
#endif
    return LV_RES_OK;
}

static lv_res_t click_action(lv_obj_t * btn)
{
    (void) btn; /*Unused*/

#if LV_EX_PRINTF
    printf("Click\n");
#endif
    return LV_RES_OK;
}

static lv_res_t long_press_action(lv_obj_t * btn)
{
    (void) btn; /*Unused*/

#if LV_EX_PRINTF
    printf("Long press\n");
#endif
    return LV_RES_OK;
}
#endif

#endif /* USE_LV_GROUP && USE_LV_TESTS */
