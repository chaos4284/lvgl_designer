#Makefile
CC = gcc

TOP_DIR = $(shell pwd)
ROOT_DIR = $(shell pwd)/libLvgl
LITTLEVGL_LVGL_DIR    = $(ROOT_DIR)/lvgl
LITTLEVGL_EXAMPLE_DIR = $(ROOT_DIR)/lv_examples
LITTLEVGL_DRIVERS_DIR = $(ROOT_DIR)/lv_drivers

IMG_NAME    = Designer

###############Compile Option#############################################
CFLAGS = -Wall -Wshadow -Wundef -Wmaybe-uninitialized -fbounds-check -fpic
CFLAGS += -O3 -g3 -I./


CFLAGS += -O3 -g3 -I./


LD_OPTION = 
LD_OPTION += -lSDL2 -lm
#LD_OPTION   += -nostdlib 
#LD_OPTION   += -nostartfiles
#LD_OPTION   += -nodefaultlibs
#LD_OPTION   += -p 
LDFLAGS =$(LD_OPTION)
DEP_OPTION  =
DEP_OPTION  += -nostdinc
DEP_OPTION  += $(INCLUDES)

###############libLvgl#############################################
###############HEADER#######################################
#lvgl_lib
LV_CORE_INC   =  $(LITTLEVGL_LVGL_DIR)/lv_core
LV_DRAW_INC   =  $(LITTLEVGL_LVGL_DIR)/lv_draw
LV_FONT_INC   =  $(LITTLEVGL_LVGL_DIR)/lv_fonts
LV_HAL_INC    =  $(LITTLEVGL_LVGL_DIR)/lv_hal
LV_MISC_INC   =  $(LITTLEVGL_LVGL_DIR)/lv_misc
LV_OBJX_INC   =  $(LITTLEVGL_LVGL_DIR)/lv_objx
LV_THEMES_INC =  $(LITTLEVGL_LVGL_DIR)/lv_themes

#driver_lib
LV_DISPLAY_INC =  $(LITTLEVGL_DRIVERS_DIR)/display
LV_INDEV_INC   =  $(LITTLEVGL_DRIVERS_DIR)/indev

#examples
LV_TEST_GROUP_INC  =  $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_group
LV_TEST_MISC_INC   =  $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_misc
LV_TEST_OBJX_INC   =  $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_objx
LV_TEST_THEME_INC  =  $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_theme
LV_TEST_OBJ_INC    =  $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_obj
LV_TEST_STRESS_INC =  $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_stress

LV_TUTORIAL_PORTING_INC       =  $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/0_porting
LV_TUTORIAL_HELLO_WORLD_INC   =  $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/1_hello_world
LV_TUTORIAL_OBJECTS_INC       =  $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/2_objects
LV_TUTORIAL_STYLES_INC        =  $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/3_styles
LV_TUTORIAL_THEMES_INC        =  $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/4_themes
LV_TUTORIAL_ANTIALIASING_INC  =  $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/5_antialiasing
LV_TUTORIAL_IMAGES_INC        =  $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/6_images
LV_TUTORIAL_FONTS_INC         =  $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/7_fonts
LV_TUTORIAL_ANIMATIONS_INC    =  $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/8_animations
LV_TUTORIAL_RESPONSIVE_INC    =  $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/9_responsive
LV_TUTORIAL_KEYBOARD_INC      =  $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/10_keyboard

LV_APPS_BENCHMARK_INC   =  $(LITTLEVGL_EXAMPLE_DIR)/lav_apps/benchmark
LV_APPS_DEMO_INC        =  $(LITTLEVGL_EXAMPLE_DIR)/lav_apps/demo
LV_APPS_SYSMON_INC      =  $(LITTLEVGL_EXAMPLE_DIR)/lav_apps/sysmon
LV_APPS_TERMINAL_INC    =  $(LITTLEVGL_EXAMPLE_DIR)/lav_apps/terminal
LV_APPS_TPCAL_INC       =  $(LITTLEVGL_EXAMPLE_DIR)/lav_apps/tpcal

#source lvgl add 
LITTLEVGL_HEADER = -I$(ROOT_DIR)
LITTLEVGL_HEADER +=  -I$(LV_CORE_INC)
LITTLEVGL_HEADER += -I$(LV_DRAW_INC)  
LITTLEVGL_HEADER += -I$(LV_FONT_INC)  
LITTLEVGL_HEADER += -I$(LV_HAL_INC)   
LITTLEVGL_HEADER += -I$(LV_MISC_INC)  
LITTLEVGL_HEADER += -I$(LV_OBJX_INC)  
LITTLEVGL_HEADER += -I$(LV_THEMES_INC)

#source driver add 
LITTLEVGL_HEADER += -I$(LV_DISPLAY_INC)
LITTLEVGL_HEADER += -I$(LV_INDEV_INC)

#source test
LITTLEVGL_HEADER += -I$(LV_TEST_GROUP_INC)
LITTLEVGL_HEADER += -I$(LV_TEST_MISC_INC)
LITTLEVGL_HEADER += -I$(LV_TEST_OBJX_INC)
LITTLEVGL_HEADER += -I$(LV_TEST_THEME_INC)
LITTLEVGL_HEADER += -I$(LV_TEST_OBJ_INC)
LITTLEVGL_HEADER += -I$(LV_TEST_STRESS_INC)

#source tutorial
LITTLEVGL_HEADER += -I$(LV_TUTORIAL_PORTING_INC)
LITTLEVGL_HEADER += -I$(LV_TUTORIAL_HELLO_WORLD_INC)
LITTLEVGL_HEADER += -I$(LV_TUTORIAL_OBJECTS_INC)
LITTLEVGL_HEADER += -I$(LV_TUTORIAL_STYLES_INC)
LITTLEVGL_HEADER += -I$(LV_TUTORIAL_THEMES_INC)
LITTLEVGL_HEADER += -I$(LV_TUTORIAL_ANTIALIASING_INC)
LITTLEVGL_HEADER += -I$(LV_TUTORIAL_IMAGES_INC)
LITTLEVGL_HEADER += -I$(LV_TUTORIAL_FONTS_INC)
LITTLEVGL_HEADER += -I$(LV_TUTORIAL_ANIMATIONS_INC)
LITTLEVGL_HEADER += -I$(LV_TUTORIAL_RESPONSIVE_INC)
LITTLEVGL_HEADER += -I$(LV_TUTORIAL_KEYBOARD_INC)

#source app
LITTLEVGL_HEADER += -I$(LV_APPS_BENCHMARK_INC)
LITTLEVGL_HEADER += -I$(LV_APPS_DEMO_INC)
LITTLEVGL_HEADER += -I$(LV_APPS_SYSMON_INC)
LITTLEVGL_HEADER += -I$(LV_APPS_TERMINAL_INC)
LITTLEVGL_HEADER += -I$(LV_APPS_TPCAL_INC)

CFLAGS += $(LITTLEVGL_HEADER)

###############SOURCE########################################
#lvgl_lib
LV_CORE_SRC   = $(wildcard $(LITTLEVGL_LVGL_DIR)/lv_core/*.c)
LV_DRAW_SRC   = $(wildcard $(LITTLEVGL_LVGL_DIR)/lv_draw/*.c)
LV_FONT_SRC   = $(wildcard $(LITTLEVGL_LVGL_DIR)/lv_fonts/*.c)
LV_HAL_SRC    = $(wildcard $(LITTLEVGL_LVGL_DIR)/lv_hal/*.c)
LV_MISC_SRC   = $(wildcard $(LITTLEVGL_LVGL_DIR)/lv_misc/*.c)
LV_OBJX_SRC   = $(wildcard $(LITTLEVGL_LVGL_DIR)/lv_objx/*.c)
LV_THEMES_SRC = $(wildcard $(LITTLEVGL_LVGL_DIR)/lv_themes/*.c)

#driver_lib
LV_DISPLAY_SRC = $(wildcard $(LITTLEVGL_DRIVERS_DIR)/display/*.c)
LV_INDEV_SRC   = $(wildcard $(LITTLEVGL_DRIVERS_DIR)/indev/*.c)

#examples
LV_TEST_GROUP_SRC  = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_group/*.c)
LV_TEST_MISC_SRC   = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_misc/*.c)
LV_TEST_OBJX_SRC   = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_objx/*.c)
LV_TEST_THEME_SRC  = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_theme/*.c)
LV_TEST_OBJ_SRC    = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_obj/*.c)
LV_TEST_STRESS_SRC = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_test/lv_test_stress/*.c)

LV_TUTORIAL_PORTING_SRC       = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/0_porting/*.c)
LV_TUTORIAL_HELLO_WORLD_SRC   = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/1_hello_world/*.c)
LV_TUTORIAL_OBJECTS_SRC       = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/2_objects/*.c)
LV_TUTORIAL_STYLES_SRC        = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/3_styles/*.c)
LV_TUTORIAL_THEMES_SRC        = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/4_themes/*.c)
LV_TUTORIAL_ANTIALIASING_SRC  = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/5_antialiasing/*.c)
LV_TUTORIAL_IMAGES_SRC        = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/6_images/*.c)
LV_TUTORIAL_FONTS_SRC         = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/7_fonts/*.c)
LV_TUTORIAL_ANIMATIONS_SRC    = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/8_animations/*.c)
LV_TUTORIAL_RESPONSIVE_SRC    = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/9_responsive/*.c)
LV_TUTORIAL_KEYBOARD_SRC      = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_tutorial/10_keyboard/*.c)

LV_APPS_BENCHMARK_SRC   = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_apps/benchmark/*.c)
LV_APPS_DEMO_SRC        = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_apps/demo/*.c)
LV_APPS_SYSMON_SRC      = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_apps/sysmon/*.c)
LV_APPS_TERMINAL_SRC    = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_apps/terminal/*.c)
LV_APPS_TPCAL_SRC       = $(wildcard $(LITTLEVGL_EXAMPLE_DIR)/lv_apps/tpcal/*.c)

#source lvgl add 
LITTLEVGL_SOURCE =  $(LV_CORE_SRC)
LITTLEVGL_SOURCE += $(LV_DRAW_SRC)  
LITTLEVGL_SOURCE += $(LV_FONT_SRC)  
LITTLEVGL_SOURCE += $(LV_HAL_SRC)   
LITTLEVGL_SOURCE += $(LV_MISC_SRC)  
LITTLEVGL_SOURCE += $(LV_OBJX_SRC)  
LITTLEVGL_SOURCE += $(LV_THEMES_SRC)

#source driver add 
LITTLEVGL_SOURCE += $(LV_DISPLAY_SRC)
LITTLEVGL_SOURCE += $(LV_INDEV_SRC)

#source test
LITTLEVGL_SOURCE += $(LV_TEST_GROUP_SRC)
LITTLEVGL_SOURCE += $(LV_TEST_MISC_SRC)
LITTLEVGL_SOURCE += $(LV_TEST_OBJX_SRC)
LITTLEVGL_SOURCE += $(LV_TEST_THEME_SRC)
LITTLEVGL_SOURCE += $(LV_TEST_OBJ_SRC)
LITTLEVGL_SOURCE += $(LV_TEST_STRESS_SRC)

#source tutorial
LITTLEVGL_SOURCE +=$(LV_TUTORIAL_PORTING_SRC)
LITTLEVGL_SOURCE +=$(LV_TUTORIAL_HELLO_WORLD_SRC)
LITTLEVGL_SOURCE +=$(LV_TUTORIAL_OBJECTS_SRC)
LITTLEVGL_SOURCE +=$(LV_TUTORIAL_STYLES_SRC)
LITTLEVGL_SOURCE +=$(LV_TUTORIAL_THEMES_SRC)
LITTLEVGL_SOURCE +=$(LV_TUTORIAL_ANTIALIASING_SRC)
LITTLEVGL_SOURCE +=$(LV_TUTORIAL_IMAGES_SRC)
LITTLEVGL_SOURCE +=$(LV_TUTORIAL_FONTS_SRC)
LITTLEVGL_SOURCE +=$(LV_TUTORIAL_ANIMATIONS_SRC)
LITTLEVGL_SOURCE +=$(LV_TUTORIAL_RESPONSIVE_SRC)
LITTLEVGL_SOURCE +=$(LV_TUTORIAL_KEYBOARD_SRC)

#source app
LITTLEVGL_SOURCE +=$(LV_APPS_BENCHMARK_SRC)
LITTLEVGL_SOURCE +=$(LV_APPS_DEMO_SRC)
LITTLEVGL_SOURCE +=$(LV_APPS_SYSMON_SRC)
LITTLEVGL_SOURCE +=$(LV_APPS_TERMINAL_SRC)
LITTLEVGL_SOURCE +=$(LV_APPS_TPCAL_SRC)

C_SRCS += $(LITTLEVGL_SOURCE)
########################################END libLvg########################

########################################libTimer################################
#Timer
TIMER_HEADER  =  -I$(TOP_DIR)/libTimer/
TIMER_SOURCE  = $(TOP_DIR)/libTimer/timer.c

C_SRCS += $(TIMER_SOURCE)
CFLAGS += $(TIMER_HEADER)
########################################libTimer################################



########################################Main Source################################
MAIN_SRC = main.c mouse_cursor_icon.c launcher.c button_management.c
MAIN_OBJ = main.o mouse_cursor_icon.o launcher.o button_management.o
########################################Main End################################

C_OBJS          = $(C_SRCS:%.c=%.o)

OBJS            = $(C_OBJS)

%.o:%.c
#	@echo ">> C compiling $< ..."
	$(CC)   -c $(CFLAGS)   -o $@ $<

all: $(MAIN_OBJ) $(OBJS)
#	@echo "qwgwqgwqgwqg ==== $(ROOT_DIR)" 
	$(CC) -o $(IMG_NAME) $(MAIN_OBJ) $(OBJS) $(LDFLAGS)
test:
	@echo "INC = $(TOPDIR)==========="
	@echo "SRc = $(LV_APPS_DEMO_SRC)===="
	@echo "test = $(LV_TUTORIAL_PORTING_SRC)=========="
	@echo "timer = $(XCP_TIMER)=============="
clean:
	rm -f $(OBJS) $(MAIN_OBJ) $(IMG_NAME)
ifeq (_depend,$(wildcard _depend))
include _depend
endif

