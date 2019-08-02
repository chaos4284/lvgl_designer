
#ifndef MAIN_H_
#define MAIN_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//#include "timer.h"
#include "lvgl/lvgl.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/keyboard.h"
#include "lv_conf.h"
#include "lvgl/src/lv_draw/lv_draw_img.h"
#include <SDL2/SDL.h>
#define SYS_TICK 10000
/*********************
 *      DEFINES
 *********************/
#define DEBUG_MSG printf("FUNCTION = %s, LINE = %d\n",__FUNCTION__,__LINE__);
/*On OSX SDL needs different handling*/
#if defined(__APPLE__) && defined(TARGET_OS_MAC)
# if __APPLE__ && TARGET_OS_MAC
#define SDL_APPLE
# endif
#endif
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
/**********************
 *      TYPEDEFS
**********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

#endif
