
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "main.h"
/*********************
 *      DEFINES
 *********************/

/*On OSX SDL needs different handling*/
#if defined(__APPLE__) && defined(TARGET_OS_MAC)
# if __APPLE__ && TARGET_OS_MAC
#define SDL_APPLE
# endif
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
extern void lv_design_set_device();
extern lv_indev_t* lv_design_get_keyboard_device_ref();
extern void lv_design_init_timer();
extern uint64_t lv_design_get_time_diff();
extern void lv_test_group_1(void);

int main(int argc, char ** argv)
{
    uint64_t diff = 0;
    lv_indev_t *key_test;
    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL (display, input devices, tick) for LittlevGL*/
    lv_design_set_device();
    /* A keyboard and encoder (mouse wheel) control example*/
    lv_design_init_timer();
   // key_test = lv_design_get_keyboard_device_ref();
//    lv_tutorial_keyboard(key_test);

    lv_design_launch_module();
    while(1) 
    {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        diff = lv_design_get_time_diff();
        if(diff > SYS_TICK)
        {         
                lv_tick_inc(SYS_TICK/1000); /*SYS_TICK(2000) / 1000 = 2ms*/
                lv_task_handler();
                lv_design_update_time();
        }
        else
        {
        }
    }


    return 0;
}
