
#include "lv_conf.h"
#include "button_management.h"
#include "launcher.h"
#include "lvgl/lvgl.h"
#include "lv_math.h"
#include <stdlib.h>
static lv_obj_t	*background_panel;

static lv_design_panel_info_t	screen_panel;
static lv_design_panel_info_t	property_panel;
static lv_design_panel_info_t	component_panel;
lv_group_t *group_input_keyboard;

static unsigned char property_input_status;

static lv_obj_t	*set_component_size_width;
static lv_obj_t	*set_component_size_height;
static lv_obj_t	*set_component_position_x;
static lv_obj_t	*set_component_position_y;

static lv_obj_t	*set_component_size_width_label;
static lv_obj_t	*set_component_size_height_label;
static lv_obj_t	*set_component_position_x_label;
static lv_obj_t	*set_component_position_y_label;

static void lv_design_draw_component();
static void lv_design_draw_screen();
static void lv_design_draw_property();
static void lv_design_draw_background();
extern void lv_design_insert_user_button(lv_deisgn_button_info_t *new_button);
extern lv_design_button_list_t* lv_design_get_button_info();
extern lv_indev_t* lv_design_get_keyboard_device_ref();
extern lv_deisgn_button_info_t *lv_design_get_button_by_id(unsigned int btn_id);

unsigned int current_btn_id = 0;

lv_res_t lv_design_user_button_press_callback(lv_obj_t* btn)
{
	volatile int a = 0;
	lv_res_t res = 0;
	lv_deisgn_button_info_t *get_user_btn_content;// = (lv_deisgn_button_info_t*)malloc(sizeof(lv_deisgn_button_info_t));
	char data[100];
	//lv_deisgn_button_info_t get_user_btn_memory;

//	get_user_btn_content = &get_user_btn_memory;

	current_btn_id = btn->free_num;
	get_user_btn_content = lv_design_get_button_by_id(current_btn_id);
	if(get_user_btn_content == NULL)
	{		return 0;
	}
	else
	{
		a= 20;
	}

	lv_obj_set_hidden(set_component_size_width,FALSE);
	lv_obj_set_hidden(set_component_size_width_label,FALSE);
	lv_obj_set_hidden(set_component_size_height,FALSE);
	lv_obj_set_hidden(set_component_size_height_label,FALSE);
	lv_obj_set_hidden(set_component_position_x, FALSE);
	lv_obj_set_hidden(set_component_position_x_label,FALSE);
	lv_obj_set_hidden(set_component_position_y,FALSE);
	lv_obj_set_hidden(set_component_position_y_label,FALSE);

	sprintf(data,"%d",get_user_btn_content->width);
	lv_ta_set_text(set_component_size_width,data);
	sprintf(data,"%d",get_user_btn_content->height);
	lv_ta_set_text(set_component_size_height,data);
	sprintf(data,"%d",get_user_btn_content->pos_x);
	lv_ta_set_text(set_component_position_x,data);
	sprintf(data,"%d",get_user_btn_content->pos_y);
	lv_ta_set_text(set_component_position_y,data);
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
		property_input_status = FALSE;
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
		lv_btn_set_action(button_info.ref_button, LV_BTN_ACTION_PR, lv_design_user_button_press_callback);
		//lv_btn_set_toggle(button_info->ref_button,true);
		lv_label_set_text(button_info.ref_label, "Button");
		lv_design_insert_user_button(&button_info);

    }
	else if(property_input_status == TRUE)
	{
		property_input_status = FALSE;
		lv_obj_set_width(lv_design_get_button_by_id(current_btn_id)->ref_button, atoi(lv_ta_get_text(set_component_size_width)));
		lv_obj_set_height(lv_design_get_button_by_id(current_btn_id)->ref_button, atoi(lv_ta_get_text(set_component_size_height)));
		lv_obj_set_x(lv_design_get_button_by_id(current_btn_id)->ref_button, atoi(lv_ta_get_text(set_component_position_x)));
		lv_obj_set_y(lv_design_get_button_by_id(current_btn_id)->ref_button, atoi(lv_ta_get_text(set_component_position_y)));
    	lv_ta_set_cursor_type(set_component_size_width,LV_CURSOR_NONE);
    	lv_ta_set_cursor_type(set_component_size_height,LV_CURSOR_NONE);
    	lv_ta_set_cursor_type(set_component_position_x,LV_CURSOR_NONE);
    	lv_ta_set_cursor_type(set_component_position_y,LV_CURSOR_NONE);
	}

    return res;
}

lv_res_t lv_design_property_process_callback(lv_obj_t * obj_property, lv_signal_t sign, void * param)
{
    lv_res_t res = 1;

    if(sign == LV_SIGNAL_PRESSED)
    {
    	property_input_status = TRUE;
    	lv_ta_set_cursor_type(set_component_size_width,LV_CURSOR_NONE);
    	lv_ta_set_cursor_type(set_component_size_height,LV_CURSOR_NONE);
    	lv_ta_set_cursor_type(set_component_position_x,LV_CURSOR_NONE);
    	lv_ta_set_cursor_type(set_component_position_y,LV_CURSOR_NONE);

    	lv_ta_set_cursor_type(obj_property,LV_CURSOR_LINE);
    	lv_group_add_obj(group_input_keyboard, obj_property);
    }
	else if(sign == LV_SIGNAL_CONTROLL)
	{
		DEBUG_MSG
		uint32_t c = *((uint32_t *)param);
//		if(c == LV_GROUP_KEY_RIGHT)     lv_ta_cursor_right(obj_property);
//		else if(c == LV_GROUP_KEY_LEFT) lv_ta_cursor_left(obj_property);
//		else if(c == LV_GROUP_KEY_UP)   lv_ta_cursor_up(obj_property);
		//else if(c == LV_GROUP_KEY_DOWN) lv_ta_cursor_down(obj_property);
		if(c == LV_GROUP_KEY_DEL)  lv_ta_del_char(obj_property);
		else if(c == LV_GROUP_KEY_DOWN)
		{
				property_input_status = FALSE;
				if(obj_property == set_component_size_width)
				{
					lv_obj_set_width(lv_design_get_button_by_id(current_btn_id)->ref_button, atoi(lv_ta_get_text(set_component_size_width)));
				}
				else if(obj_property == set_component_size_height)
				{
					lv_obj_set_height(lv_design_get_button_by_id(current_btn_id)->ref_button, atoi(lv_ta_get_text(set_component_size_height)));
				}
				else if(obj_property == set_component_position_x)
				{
					lv_obj_set_x(lv_design_get_button_by_id(current_btn_id)->ref_button, atoi(lv_ta_get_text(set_component_position_x)));
				}
				else if(obj_property == set_component_position_y)
				{
					lv_obj_set_y(lv_design_get_button_by_id(current_btn_id)->ref_button, atoi(lv_ta_get_text(set_component_position_y)));
				}
		    	lv_ta_set_cursor_type(set_component_size_width,LV_CURSOR_NONE);
		    	lv_ta_set_cursor_type(set_component_size_height,LV_CURSOR_NONE);
		    	lv_ta_set_cursor_type(set_component_position_x,LV_CURSOR_NONE);
		    	lv_ta_set_cursor_type(set_component_position_y,LV_CURSOR_NONE);


		}
		else
		{
			lv_ta_add_char(obj_property, c);
		}
    }


    return res;

}

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
	property_input_status = FALSE;

	lv_obj_set_size(property_panel.ref_panel,property_panel.panel_width,property_panel.panel_height);
	lv_obj_align(property_panel.ref_panel, NULL, LV_ALIGN_IN_TOP_RIGHT, property_panel.pos_x, property_panel.pos_y);

	set_component_size_width = lv_ta_create(property_panel.ref_panel,NULL);
	set_component_size_height = lv_ta_create(property_panel.ref_panel,NULL);
	set_component_position_x = lv_ta_create(property_panel.ref_panel,NULL);
	set_component_position_y = lv_ta_create(property_panel.ref_panel,NULL);

	set_component_size_width_label = lv_label_create(property_panel.ref_panel, NULL);
	set_component_size_height_label = lv_label_create(property_panel.ref_panel, NULL);
	set_component_position_x_label = lv_label_create(property_panel.ref_panel, NULL);
	set_component_position_y_label = lv_label_create(property_panel.ref_panel, NULL);
	lv_label_set_align(set_component_size_width_label, LV_LABEL_ALIGN_CENTER);
	lv_label_set_align(set_component_size_height_label, LV_LABEL_ALIGN_CENTER);
	lv_label_set_align(set_component_position_x_label, LV_LABEL_ALIGN_CENTER);
	lv_label_set_align(set_component_position_y_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_width(set_component_size_width_label, property_panel.panel_width - 1);
	lv_obj_set_width(set_component_size_height_label, property_panel.panel_width - 1);
	lv_obj_set_width(set_component_position_x_label, property_panel.panel_width - 1);
	lv_obj_set_width(set_component_position_y_label, property_panel.panel_width - 1);
	lv_label_set_text(set_component_size_width_label, "Wdith");
	lv_label_set_text(set_component_size_height_label, "Height");
	lv_label_set_text(set_component_position_x_label, "Position X");
	lv_label_set_text(set_component_position_y_label, "Position Y");

	//set_component_size_width
	lv_ta_set_cursor_type(set_component_size_width,LV_CURSOR_NONE);
	lv_obj_set_width(set_component_size_width, property_panel.panel_width - 1);
	lv_ta_set_max_length(set_component_size_width,5);
	lv_ta_set_one_line(set_component_size_width, true);
	lv_ta_set_text(set_component_size_width, "");
	lv_obj_set_signal_func(set_component_size_width,lv_design_property_process_callback);
	lv_obj_set_pos(set_component_size_width, lv_obj_get_x(set_component_size_width), lv_obj_get_y(property_panel.ref_panel) );
	lv_obj_set_pos(set_component_size_width_label, lv_obj_get_x(set_component_size_width) + 10, lv_obj_get_y(set_component_size_width)-20);
	lv_obj_set_hidden(set_component_size_width,TRUE);
	lv_obj_set_hidden(set_component_size_width_label,TRUE);
	//set_component_size_height
	lv_ta_set_cursor_type(set_component_size_height,LV_CURSOR_NONE);
	lv_obj_set_width(set_component_size_height, property_panel.panel_width - 1);
	lv_ta_set_max_length(set_component_size_height,5);
	lv_ta_set_one_line(set_component_size_height, true);
	lv_ta_set_text(set_component_size_height, "");
	lv_obj_set_signal_func(set_component_size_height,lv_design_property_process_callback);
	lv_obj_set_pos(set_component_size_height, lv_obj_get_x(set_component_size_width), lv_obj_get_y(set_component_size_width) + 80);
	lv_obj_set_pos(set_component_size_height_label, lv_obj_get_x(set_component_size_height) + 10, lv_obj_get_y(set_component_size_height)-20);
	lv_obj_set_hidden(set_component_size_height,TRUE);
	lv_obj_set_hidden(set_component_size_height_label,TRUE);

	//set_component_position_x
	lv_ta_set_cursor_type(set_component_position_x,LV_CURSOR_NONE);
	lv_obj_set_width(set_component_position_x, property_panel.panel_width - 1);
	lv_ta_set_max_length(set_component_position_x,5);
	lv_ta_set_one_line(set_component_position_x, true);
	lv_ta_set_text(set_component_position_x, "");
	lv_obj_set_signal_func(set_component_position_x,lv_design_property_process_callback);
	lv_obj_set_pos(set_component_position_x, lv_obj_get_x(set_component_size_width), lv_obj_get_y(set_component_size_height) + 80);
	lv_obj_set_pos(set_component_position_x_label, lv_obj_get_x(set_component_position_x) + 10, lv_obj_get_y(set_component_position_x)-20);
	lv_obj_set_hidden(set_component_position_x,TRUE);
	lv_obj_set_hidden(set_component_position_x_label,TRUE);

	//set_component_position_y
	lv_ta_set_cursor_type(set_component_position_y,LV_CURSOR_NONE);
	lv_obj_set_width(set_component_position_y, property_panel.panel_width - 1);
	lv_ta_set_max_length(set_component_position_y,5);
	lv_ta_set_one_line(set_component_position_y, true);
	lv_ta_set_text(set_component_position_y, "");
	lv_obj_set_signal_func(set_component_position_y,lv_design_property_process_callback);
	lv_obj_set_pos(set_component_position_y, lv_obj_get_x(set_component_size_width), lv_obj_get_y(set_component_position_x )+ 80);
	lv_obj_set_pos(set_component_position_y_label, lv_obj_get_x(set_component_position_y) + 10, lv_obj_get_y(set_component_position_y)-20);
	lv_obj_set_hidden(set_component_position_y,TRUE);
	lv_obj_set_hidden(set_component_position_y_label,TRUE);

	group_input_keyboard = lv_group_create();
	lv_indev_set_group(lv_design_get_keyboard_device_ref(), group_input_keyboard);
}
static void lv_design_draw_background()
{
    //static lv_obj_t * control_btn_label;               /*A label for the demo*/
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
//	DEBUG_MSG
}







	
