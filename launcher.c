
#include "lv_conf.h"
#include "button_management.h"
#include "launcher.h"
#include "lvgl/lvgl.h"
#include "lv_math.h"
static lv_obj_t	*background_panel;

static lv_design_panel_info_t	screen_panel;
static lv_design_panel_info_t	property_panel;
static lv_design_panel_info_t	component_panel;
lv_group_t *group_input_keyboard;
static lv_obj_t	*text_area;
static void lv_design_draw_component();
static void lv_design_draw_screen();
static void lv_design_draw_property();
static void lv_design_draw_background();
extern void lv_design_insert_user_button(lv_deisgn_button_info_t *new_button);
extern lv_design_button_list_t* lv_design_get_button_info();
extern lv_indev_t* lv_design_get_keyboard_device_ref();
static click_count = 0;
static lv_design_func_t ancestor_design;
static lv_design_func_t scrl_design;
static lv_signal_func_t ancestor_signal;
static lv_signal_func_t scrl_signal;
unsigned int current_btn_id = 0;
static void lv_design_draw_component()
{
	component_panel.panel_width = LV_HOR_RES/5;
	component_panel.panel_height = LV_VER_RES - (LV_VER_RES / 4);
	component_panel.ref_panel = lv_obj_create(background_panel,NULL);
	component_panel.pos_x = 0;
	component_panel.pos_y = 30;
	lv_obj_set_size(component_panel.ref_panel, component_panel.panel_width , component_panel.panel_height);
	lv_obj_align(component_panel.ref_panel, NULL, LV_ALIGN_IN_TOP_LEFT, component_panel.pos_x, component_panel.pos_y);
	lv_design_init_button_component();
}

static void lv_design_draw_screen()
{
	screen_panel.panel_width =  LV_VER_RES - (LV_VER_RES / 4);
	screen_panel.panel_height = LV_HOR_RES/2;
//	printf("screen_panel.ref_panel_X = %d\n",screen_panel.panel_width);
//	printf("screen_panel.ref_panel_Y = %d\n",screen_panel.panel_height);
	screen_panel.ref_panel = lv_obj_create(background_panel,NULL);
	screen_panel.pos_x = 0;
	screen_panel.pos_y = 30;
	lv_obj_set_size(screen_panel.ref_panel, screen_panel.panel_width, screen_panel.panel_height);
	lv_obj_align(screen_panel.ref_panel, NULL, LV_ALIGN_IN_TOP_MID, screen_panel.pos_x, screen_panel.pos_y);
	lv_obj_set_signal_func(screen_panel.ref_panel,lv_design_screen_press_callback);

}

static void lv_design_draw_property()
{
	property_panel.panel_width =  LV_HOR_RES/5;
	property_panel.panel_height =LV_VER_RES - (LV_VER_RES / 4);
	property_panel.ref_panel = lv_obj_create(background_panel,NULL);
	property_panel.pos_x = 0;
	property_panel.pos_y = 30;
    lv_obj_set_size(property_panel.ref_panel,property_panel.panel_width,property_panel.panel_height);
    lv_obj_align(property_panel.ref_panel, NULL, LV_ALIGN_IN_TOP_RIGHT, property_panel.pos_x, property_panel.pos_y);
}
static void lv_design_draw_background()
{
    background_panel = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(background_panel, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(background_panel, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_obj_set_style(background_panel, &lv_style_pretty);
}

lv_design_panel_info_t* lv_design_get_component_panel()
{
	return &component_panel;
}

void lv_design_launch_module()
{
	lv_design_draw_background();
	lv_design_draw_screen();
	lv_design_draw_component();
	lv_design_draw_property();
}
lv_res_t test_ta(lv_obj_t * ta, lv_signal_t sign, void * param)
{
    lv_res_t res;

    if(sign == LV_SIGNAL_PRESSED)
    {
    	lv_ta_set_cursor_type(text_area,LV_CURSOR_LINE);
    }
	else if(sign == LV_SIGNAL_CONTROLL)
	{
		uint32_t c = *((uint32_t *)param);      /*uint32_t because can be UTF-8*/
		if(c == LV_GROUP_KEY_RIGHT)     lv_ta_cursor_right(ta);
		else if(c == LV_GROUP_KEY_LEFT) lv_ta_cursor_left(ta);
		else if(c == LV_GROUP_KEY_UP)   lv_ta_cursor_up(ta);
		else if(c == LV_GROUP_KEY_DOWN) lv_ta_cursor_down(ta);
		else if(c == LV_GROUP_KEY_DEL)  lv_ta_del_char(ta);
		else if(c == LV_GROUP_KEY_ENTER)
		{
			printf("Enter Press\n");
			
			lv_obj_set_width(lv_design_get_button_by_id(current_btn_id), atoi(lv_ta_get_text(text_area)));
		}
		else
		{
			lv_ta_add_char(ta, c);
		}
    }


    return res;

}
lv_res_t lv_test_btn_callback(lv_obj_t* btn)
{
	lv_res_t res = 0;
	lv_obj_t * content;
	char data[100];
	current_btn_id = btn->free_num;
	group_input_keyboard = lv_group_create();
	text_area = lv_ta_create(property_panel.ref_panel,NULL);
	lv_indev_set_group(lv_design_get_keyboard_device_ref(), group_input_keyboard);
	lv_group_add_obj(group_input_keyboard, text_area);

	lv_ta_set_cursor_type(text_area,LV_CURSOR_NONE);
	lv_obj_set_width(text_area, LV_MATH_MIN(100, LV_DPI * 3 / 2));
    lv_ta_set_max_length(text_area,5);
    lv_ta_set_one_line(text_area, true);
    lv_ta_set_text(text_area, "");

   lv_obj_set_signal_func(text_area,test_ta);

	return res;
}
lv_res_t lv_design_screen_press_callback(lv_obj_t * btn, lv_signal_t sign, void * param)
{
	lv_res_t res = 0;
	lv_coord_t parent_x;
	lv_coord_t parent_y;
	lv_point_t pos;
	lv_indev_t * indev;
	unsigned int button_component_pressed;
	lv_deisgn_button_info_t button_info;
	//button_info = (lv_deisgn_button_info_t*)malloc(sizeof(lv_deisgn_button_info_t));
	button_component_pressed = lv_design_get_button_component_press_state();
	lv_design_button_list_t *get_user_btn_info;
    if(button_component_pressed == 1)
    {

    	get_user_btn_info = lv_design_get_button_info();
    	get_user_btn_info->btn_count++;
    	lv_design_set_button_component_press_state(FALSE);
    	lv_btn_set_state(lv_design_get_button_component_ref(),LV_BTN_STATE_REL);
		parent_x = lv_obj_get_x(screen_panel.ref_panel);
		parent_y = lv_obj_get_y(screen_panel.ref_panel);
		indev = lv_indev_get_act();
		lv_indev_get_point(indev, &pos);

		button_info.width = 100;
		button_info.height = 50;
		button_info.pos_x = pos.x -parent_x;
		button_info.pos_y = pos.y -parent_y;
		button_info.ref_button = lv_btn_create(screen_panel.ref_panel, NULL);
		button_info.ref_label = lv_label_create(button_info.ref_button, NULL);
		button_info.ref_button->free_num = get_user_btn_info->btn_count;
		lv_obj_set_size(button_info.ref_button, button_info.width, button_info.height);

		lv_obj_set_pos(button_info.ref_button, button_info.pos_x, button_info.pos_y);
		lv_obj_set_style(button_info.ref_button, &lv_style_pretty);
		lv_btn_set_action(button_info.ref_button, LV_BTN_ACTION_PR, lv_test_btn_callback);
		//lv_btn_set_toggle(button_info->ref_button,true);
		lv_label_set_text(button_info.ref_label, "Button");
		lv_design_insert_user_button(&button_info);

    }


    return res;
}





	
