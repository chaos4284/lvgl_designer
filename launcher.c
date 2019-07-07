#include "lv_conf.h"
#include "button_management.h"
#include "launcher.h"
#include "lvgl/lvgl.h"
#include "lv_math.h"
#include <stdlib.h>
static lv_obj_t	*background_panel;
static lv_obj_t	*screen_container_page;
static lv_design_panel_info_t	screen_panel;
static lv_design_panel_info_t	property_panel;
static lv_design_panel_info_t	component_panel;
lv_group_t *group_input_keyboard;

static unsigned char property_input_status;
static lv_obj_t	*current_input_property;

static lv_obj_t	*set_component_name;
static lv_obj_t	*set_component_size_width;
static lv_obj_t	*set_component_size_height;
static lv_obj_t	*set_component_position_x;
static lv_obj_t	*set_component_position_y;

static lv_obj_t	*set_component_name_label;
static lv_obj_t	*set_component_size_width_label;
static lv_obj_t	*set_component_size_height_label;
static lv_obj_t	*set_component_position_x_label;
static lv_obj_t	*set_component_position_y_label;
static lv_design_attribute_position_t area_position[PROPERTY_COUNT];

static void lv_design_draw_component();
static void lv_design_draw_screen();
static void lv_design_draw_property();
static void lv_design_draw_background();
static void lv_design_draw_ui_preview();

extern void lv_design_insert_user_button(lv_deisgn_button_info_t *new_button);
extern lv_design_button_list_t* lv_design_get_button_info();
extern lv_indev_t* lv_design_get_keyboard_device_ref();
extern lv_deisgn_button_info_t *lv_design_get_button_by_id(unsigned int btn_id);
extern int lv_design_get_selected_button_id();

void lv_design_set_screen_panel_press_state(unsigned char screen_panel_press_state);
void lv_design_set_current_selected_component(unsigned char selected_component);
void lv_design_hidden_property(int component,bool hidden_flag);
lv_design_attribute_position_t* lv_design_get_attribute_position(void);
void lv_design_remove_current_selected_property_componet();

unsigned int lv_design_get_current_selected_component(void);
unsigned int current_selected_component = SELECTED_INIT;
lv_obj_t * prev_obj = NULL;

void lv_design_display_property_window(int attribute , lv_design_attribute_position_t *pos, char* content)
{

	switch(attribute)
	{
		case	SELECTED_NAME:
				lv_obj_set_pos(set_component_name, pos->attr_pos_x,pos->attr_pos_y);
				lv_obj_set_pos(set_component_name_label, pos->attr_pos_x + 10, pos->attr_pos_y -20);
				lv_ta_set_text(set_component_name,content);
				break;

		case	SELECTED_WIDTH:
				lv_obj_set_pos(set_component_size_width, pos->attr_pos_x,pos->attr_pos_y);
				lv_obj_set_pos(set_component_size_width_label, pos->attr_pos_x + 10, pos->attr_pos_y -20);
				lv_ta_set_text(set_component_size_width,content);
				break;

		case	SELECTED_HEIGHT:
				lv_obj_set_pos(set_component_size_height, pos->attr_pos_x,pos->attr_pos_y);
				lv_obj_set_pos(set_component_size_height_label, pos->attr_pos_x + 10, pos->attr_pos_y -20);
				lv_ta_set_text(set_component_size_height,content);
				break;

		case	SELECTED_POS_X:
				lv_obj_set_pos(set_component_position_x, pos->attr_pos_x,pos->attr_pos_y);
				lv_obj_set_pos(set_component_position_x_label, pos->attr_pos_x + 10, pos->attr_pos_y -20);
				lv_ta_set_text(set_component_position_x,content);
				break;

		case	SELECTED_POS_Y:
				lv_obj_set_pos(set_component_position_y, pos->attr_pos_x,pos->attr_pos_y);
				lv_obj_set_pos(set_component_position_y_label, pos->attr_pos_x + 10, pos->attr_pos_y -20);
				lv_ta_set_text(set_component_position_y,content);
				break;
	}
}


void lv_design_hidden_property(int component,bool hidden_flag)
{

	switch(component)
	{
		case SELECTED_INIT:
		case SELECTED_BUTTON:
			lv_obj_set_hidden(set_component_name,hidden_flag);
			lv_obj_set_hidden(set_component_name_label,hidden_flag);
			lv_obj_set_hidden(set_component_size_width,hidden_flag);
			lv_obj_set_hidden(set_component_size_width_label,hidden_flag);
			lv_obj_set_hidden(set_component_size_height,hidden_flag);
			lv_obj_set_hidden(set_component_size_height_label,hidden_flag);
			lv_obj_set_hidden(set_component_position_x, hidden_flag);
			lv_obj_set_hidden(set_component_position_x_label,hidden_flag);
			lv_obj_set_hidden(set_component_position_y,hidden_flag);
			lv_obj_set_hidden(set_component_position_y_label,hidden_flag);
			break;

		case SELECTED_SCREEN:
			lv_obj_set_hidden(set_component_size_width,hidden_flag);
			lv_obj_set_hidden(set_component_size_width_label,hidden_flag);
			lv_obj_set_hidden(set_component_size_height,hidden_flag);
			lv_obj_set_hidden(set_component_size_height_label,hidden_flag);
			break;

	}
}
unsigned int  lv_design_get_propery_pressed_status()
{
	unsigned int ret = 0;
	ret = property_input_status;

	return ret;

}

void lv_design_set_propery_pressed_status(unsigned int status)
{
	property_input_status = status;
}
void lv_design_set_current_selected_component(unsigned char selected_component)
{
	current_selected_component = selected_component;
	printf("selected_component = %d\n",selected_component);
}

unsigned int lv_design_get_current_selected_component()
{
	unsigned int ret = 0;
	ret = current_selected_component;
	return ret;
}

void lv_design_remove_current_selected_property_componet()
{
	lv_group_remove_obj(current_input_property);
	lv_ta_set_cursor_type(current_input_property,LV_CURSOR_NONE);
	prev_obj = NULL;
	current_input_property = NULL;

}
lv_res_t lv_design_pressed_preview_button_callback(lv_obj_t* preview_btn)
{
	lv_res_t res = 0;
	int btn_index=  0;
	lv_obj_t* draw_screen_view = lv_obj_create(lv_scr_act(), NULL);
	lv_design_button_list_t *get_user_button_list;
	lv_deisgn_button_info_t *get_user_btn_content;
//	lv_obj_set_size(draw_screen_view, screen_panel.panel_width,screen_panel.panel_height );
//	lv_obj_align(background_panel, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
//	lv_obj_set_style(background_panel, &lv_style_pretty);
	lv_obj_set_hidden(background_panel,TRUE);

	lv_obj_set_parent(screen_container_page,draw_screen_view);
//	get_user_button_list = lv_design_get_button_info();
/*
	for(btn_index = 1; btn_index <= get_user_button_list->btn_count;btn_index++)
	{
		get_user_btn_content = lv_design_get_button_by_id(btn_index);
		printf("get_user_btn_content x = %d\n",get_user_btn_content->pos_x);
		lv_obj_set_parent(get_user_btn_content->ref_button,draw_screen_view);
		lv_obj_set_size(get_user_btn_content->ref_button, get_user_btn_content->width, get_user_btn_content->height);
		lv_obj_align(get_user_btn_content->ref_button,NULL,LV_ALIGN_IN_TOP_LEFT,get_user_btn_content->pos_x, get_user_btn_content->pos_y);
	}
*/


	return res;
}

/* It management Draw Screen Area where components are placed*/
lv_res_t lv_design_screen_press_callback(lv_obj_t * btn, lv_signal_t sign, void * param)
{
	lv_res_t res = 0;
	lv_point_t pos;
	lv_indev_t * indev;
	lv_deisgn_button_info_t button_info;
	lv_deisgn_button_info_t *get_user_btn_content;
	lv_design_button_list_t *get_user_btn_info;
	char data[100] = {0,};
    unsigned int get_component = 0;
	if(lv_design_get_button_component_press_state() == TRUE)
	{
		property_input_status = FALSE;
		if (current_input_property != NULL)
		{
			printf("LINE = %d\n",__LINE__);
			lv_group_remove_obj(current_input_property);
			lv_ta_set_cursor_type(current_input_property,LV_CURSOR_NONE);
			prev_obj = NULL;
			current_input_property = NULL;
		}

		get_user_btn_info = lv_design_get_button_info();
		get_user_btn_info->btn_count++;
		lv_design_set_button_component_press_state(FALSE);

		lv_btn_set_state(lv_design_get_button_component_ref(),LV_BTN_STATE_REL);
		indev = lv_indev_get_act();
		lv_indev_get_point(indev, &pos);

		button_info.width = 100;
		button_info.height = 50;
		button_info.pos_x = pos.x - btn->coords.x1 ;
		button_info.pos_y = pos.y - btn->coords.y1 ;
		button_info.ref_button = lv_btn_create(screen_panel.ref_panel, NULL);

		button_info.ref_label = lv_label_create(button_info.ref_button, NULL);
		button_info.ref_button->free_num = get_user_btn_info->btn_count;
		printf("button_info.ref_button->free_num = %d\n",button_info.ref_button->free_num);

		lv_obj_set_size(button_info.ref_button, button_info.width, button_info.height);
		lv_obj_set_pos(button_info.ref_button, button_info.pos_x, button_info.pos_y);
		lv_obj_set_drag(button_info.ref_button, true);

		lv_design_insert_user_button(&button_info);
		lv_obj_set_signal_func(button_info.ref_button, lv_design_manage_position_of_user_button_callback);
		lv_label_set_text(button_info.ref_label, "Button");
	}
	else
	{

		if(property_input_status == TRUE)
		{
			property_input_status = FALSE;

			get_component = lv_design_get_current_selected_component();
			if (current_input_property != NULL)
			{
				lv_group_remove_obj(current_input_property);
				printf("remove status\n");
				lv_ta_set_cursor_type(current_input_property,LV_CURSOR_NONE);
				prev_obj = NULL;
				current_input_property = NULL;
			}

			if(get_component == SELECTED_SCREEN)
			{

			}
			else if(get_component == SELECTED_BUTTON)
			{
				int selecte_btn_id = lv_design_get_selected_button_id();
				get_user_btn_content = lv_design_get_button_by_id(selecte_btn_id);

				lv_label_set_text(get_user_btn_content->ref_label,lv_ta_get_text(set_component_name));
				lv_obj_set_width(get_user_btn_content->ref_button, atoi(lv_ta_get_text(set_component_size_width)));
				lv_obj_set_height(get_user_btn_content->ref_button, atoi(lv_ta_get_text(set_component_size_height)));
				lv_obj_set_x(get_user_btn_content->ref_button, atoi(lv_ta_get_text(set_component_position_x)));
				lv_obj_set_y(get_user_btn_content->ref_button, atoi(lv_ta_get_text(set_component_position_y)));

				get_user_btn_content->width = atoi(lv_ta_get_text(set_component_size_width));
				get_user_btn_content->height = atoi(lv_ta_get_text(set_component_size_height));
				get_user_btn_content->pos_x = atoi(lv_ta_get_text(set_component_position_x));
				get_user_btn_content->pos_y = atoi(lv_ta_get_text(set_component_position_y));

				lv_ta_set_cursor_type(set_component_name,LV_CURSOR_NONE);
				lv_ta_set_cursor_type(set_component_size_width,LV_CURSOR_NONE);
				lv_ta_set_cursor_type(set_component_size_height,LV_CURSOR_NONE);
				lv_ta_set_cursor_type(set_component_position_x,LV_CURSOR_NONE);
				lv_ta_set_cursor_type(set_component_position_y,LV_CURSOR_NONE);
				prev_obj = NULL;
			}
			else
			{
				;
			}

		}

		if(sign == LV_SIGNAL_PRESSED)
		{
			lv_design_hidden_property(SELECTED_INIT,TRUE);
			lv_design_hidden_property(SELECTED_SCREEN,FALSE);
			sprintf(data,"%d",screen_panel.panel_width);
			lv_design_display_property_window(SELECTED_WIDTH,&area_position[0],data);
			sprintf(data,"%d",screen_panel.panel_height);
			lv_design_display_property_window(SELECTED_HEIGHT,&area_position[1],data);

			lv_design_set_current_selected_component(SELECTED_SCREEN);
		}
		else if(sign == LV_SIGNAL_PRESSING)
		{
			lv_design_set_screen_panel_press_state(FALSE); /*This is a code for movement of Screnn Panel.*/
		}
		else if(sign == LV_SIGNAL_PRESS_LOST)
		{
			lv_design_set_screen_panel_press_state(TRUE); /*This is a code for obtaining pressed state of the Screen Panel.*/
		}
		else
		{
			;
		}
	}

	return res;
}

lv_res_t lv_design_property_process_callback(lv_obj_t * obj_property, lv_signal_t sign, void * param)
{
    lv_res_t res = 1;
    char text_data[100];
    lv_deisgn_button_info_t *get_user_btn_content;// = (lv_deisgn_button_info_t*)malloc(sizeof(lv_deisgn_button_info_t));

    if(sign == LV_SIGNAL_PRESSED)
    {
    	printf("signal Pressed\n");
    	if(lv_design_get_current_selected_component() == SELECTED_BUTTON)
    	{
    		printf("seleted button\n");
			lv_ta_set_cursor_type(set_component_name,LV_CURSOR_NONE);
			lv_ta_set_cursor_type(set_component_size_width,LV_CURSOR_NONE);
			lv_ta_set_cursor_type(set_component_size_height,LV_CURSOR_NONE);
			lv_ta_set_cursor_type(set_component_position_x,LV_CURSOR_NONE);
			lv_ta_set_cursor_type(set_component_position_y,LV_CURSOR_NONE);

    	}
    	else if(lv_design_get_current_selected_component() == SELECTED_SCREEN)
    	{
    		printf("seleted screen\n");
			lv_ta_set_cursor_type(set_component_size_width,LV_CURSOR_NONE);
			lv_ta_set_cursor_type(set_component_size_height,LV_CURSOR_NONE);

    	}
    	else
    	{
    		;
    	}

    	property_input_status = TRUE;
    	if(prev_obj == obj_property)
    	{
    		printf("component for ecall\n");
    		;
    	}
    	else
    	{
    		if(prev_obj == NULL)
    		{
		        printf("group add null\n");
    	   		lv_group_add_obj(group_input_keyboard, obj_property);
    			prev_obj = obj_property;

    		}
    		else
    		{
    	   		lv_group_add_obj(group_input_keyboard, obj_property);
    	   		lv_group_remove_obj(prev_obj);
    	   		printf("remove obj\n");
    			prev_obj = obj_property;
    		}
    	}
    	current_input_property = obj_property;
    	lv_ta_set_cursor_type(obj_property,LV_CURSOR_LINE);
    }
    else if(sign == LV_SIGNAL_FOCUS)
    {
    	printf("focus\n");
    }
	else if(sign == LV_SIGNAL_CONTROLL)
	{
		uint32_t key = *((uint32_t *)param);
		if((key == LV_GROUP_KEY_DEL) || (key == LV_GROUP_KEY_BACKSPACE))
		{
			lv_ta_del_char(obj_property);
		}
		else if(key == LV_GROUP_KEY_ENTER)
		{
			property_input_status = FALSE;
			if(lv_design_get_current_selected_component() == SELECTED_BUTTON)
			{
				get_user_btn_content = lv_design_get_button_by_id(lv_design_get_selected_button_id());
			}
			if(obj_property == set_component_name)
			{
				strcpy(text_data,lv_ta_get_text(set_component_name));
				lv_label_set_text(get_user_btn_content->ref_label, text_data);
			}
			else if(obj_property == set_component_size_width)
			{

				if(lv_design_get_current_selected_component() == SELECTED_BUTTON)
				{
					lv_obj_set_width(get_user_btn_content->ref_button, atoi(lv_ta_get_text(set_component_size_width)));
					get_user_btn_content->width = atoi(lv_ta_get_text(set_component_size_width));
				}
				else if(lv_design_get_current_selected_component() == SELECTED_SCREEN)
				{
					lv_obj_set_width(screen_panel.ref_panel, atoi(lv_ta_get_text(set_component_size_width)));
					screen_panel.panel_width = atoi(lv_ta_get_text(set_component_size_width));
				}
			}
			else if(obj_property == set_component_size_height)
			{
				if(lv_design_get_current_selected_component() == SELECTED_BUTTON)
				{
					lv_obj_set_height(get_user_btn_content->ref_button, atoi(lv_ta_get_text(set_component_size_height)));
					get_user_btn_content->height = atoi(lv_ta_get_text(set_component_size_height));
				}
				else if(lv_design_get_current_selected_component() == SELECTED_SCREEN)
				{
					lv_obj_set_height(screen_panel.ref_panel, atoi(lv_ta_get_text(set_component_size_height)));
					screen_panel.panel_height = atoi(lv_ta_get_text(set_component_size_height));
				}
			}
			else if(obj_property == set_component_position_x)
			{
				lv_obj_set_x(get_user_btn_content->ref_button, atoi(lv_ta_get_text(set_component_position_x)));
				get_user_btn_content->pos_x = atoi(lv_ta_get_text(set_component_position_x));
			}
			else if(obj_property == set_component_position_y)
			{
				lv_obj_set_y(get_user_btn_content->ref_button, atoi(lv_ta_get_text(set_component_position_y)));
				get_user_btn_content->pos_x = atoi(lv_ta_get_text(set_component_position_y));
			}
		    lv_ta_set_cursor_type(set_component_name,LV_CURSOR_NONE);
		    lv_ta_set_cursor_type(set_component_size_width,LV_CURSOR_NONE);
		    lv_ta_set_cursor_type(set_component_size_height,LV_CURSOR_NONE);
		    lv_ta_set_cursor_type(set_component_position_x,LV_CURSOR_NONE);
		    lv_ta_set_cursor_type(set_component_position_y,LV_CURSOR_NONE);
		    current_input_property = NULL;
		}
		else if((key >= 0 ) && (key <= 127))
		{
			if(keyboard_get_pressed_shift() == TRUE)
			{
				if((key >= 0x41) && (key <= 0x5A))
				{
					key += 0x20;
				}
				else if((key >= 0x61) && (key <= 0x7A))
				{
					key -= 0x20;
				}
			}
			lv_ta_add_char(obj_property, key);
		}
		else
		{

		}
    }
    return res;
}

static void lv_design_draw_component()
{
	component_panel.panel_width = LV_HOR_RES/5;
	component_panel.panel_height = LV_HOR_RES/2;
	component_panel.ref_panel = lv_obj_create(background_panel,NULL);
	component_panel.pos_x = 0;
	component_panel.pos_y = 40;
	lv_obj_set_size(component_panel.ref_panel, component_panel.panel_width , component_panel.panel_height);
	lv_obj_align(component_panel.ref_panel, NULL, LV_ALIGN_IN_TOP_LEFT, component_panel.pos_x, component_panel.pos_y);
	lv_design_init_button_component();
}

static void lv_design_draw_screen()
{
	/*Create a scroll bar style*/
	static lv_style_t style_sb;
	lv_style_copy(&style_sb, &lv_style_plain);
	style_sb.body.main_color = LV_COLOR_BLACK;
	style_sb.body.grad_color = LV_COLOR_BLACK;
	style_sb.body.border.color = LV_COLOR_WHITE;
	style_sb.body.border.width = 1;
	style_sb.body.border.opa = LV_OPA_70;
	style_sb.body.radius = LV_RADIUS_CIRCLE;
	style_sb.body.opa = LV_OPA_60;
	style_sb.body.padding.ver = 0;          /*Horizontal padding on the right*/
	style_sb.body.padding.hor = 0;          /*Horizontal padding on the right*/
	style_sb.body.padding.inner = 8;        /*Scrollbar width*/

	screen_container_page = lv_page_create(background_panel,NULL);
	screen_panel.panel_width =  LV_VER_RES - (LV_VER_RES / 4);
	screen_panel.panel_height = LV_HOR_RES/2;
	screen_panel.ref_panel = lv_obj_create(screen_container_page,NULL);
	screen_panel.pos_x = 0;
	screen_panel.pos_y = 40;

	lv_obj_set_size(screen_container_page,screen_panel.panel_width, screen_panel.panel_height);
	lv_obj_align(screen_container_page, NULL, LV_ALIGN_IN_TOP_MID, screen_panel.pos_x, screen_panel.pos_y);
	lv_cont_set_fit(lv_page_get_scrl(screen_container_page), true, true);
	lv_page_set_sb_mode(screen_container_page, LV_SB_MODE_AUTO);
	lv_page_set_style(screen_container_page, LV_PAGE_STYLE_SB, &style_sb);

	lv_obj_set_top(screen_panel.ref_panel, TRUE);
	lv_obj_set_size(screen_panel.ref_panel, screen_panel.panel_width, screen_panel.panel_height);
	lv_obj_align(screen_panel.ref_panel, NULL, LV_ALIGN_IN_TOP_MID, screen_panel.pos_x, screen_panel.pos_y);
	lv_obj_set_signal_func(screen_panel.ref_panel,lv_design_screen_press_callback);
	lv_obj_set_click(screen_panel.ref_panel,TRUE);

}

static void lv_design_draw_property()
{
	property_panel.panel_width =  LV_HOR_RES/5;
	property_panel.panel_height = LV_HOR_RES/2;
	property_panel.ref_panel = lv_obj_create(background_panel,NULL);
	property_panel.pos_x = 0;
	property_panel.pos_y = 40;
	property_input_status = FALSE;
	current_input_property = NULL;

	lv_obj_set_size(property_panel.ref_panel,property_panel.panel_width,property_panel.panel_height);
	lv_obj_align(property_panel.ref_panel, NULL, LV_ALIGN_IN_TOP_RIGHT, property_panel.pos_x, property_panel.pos_y);

	set_component_name = lv_ta_create(property_panel.ref_panel,NULL);
	set_component_size_width = lv_ta_create(property_panel.ref_panel,NULL);
	set_component_size_height = lv_ta_create(property_panel.ref_panel,NULL);
	set_component_position_x = lv_ta_create(property_panel.ref_panel,NULL);
	set_component_position_y = lv_ta_create(property_panel.ref_panel,NULL);

	set_component_name_label = lv_label_create(property_panel.ref_panel, NULL);
	set_component_size_width_label = lv_label_create(property_panel.ref_panel, NULL);
	set_component_size_height_label = lv_label_create(property_panel.ref_panel, NULL);
	set_component_position_x_label = lv_label_create(property_panel.ref_panel, NULL);
	set_component_position_y_label = lv_label_create(property_panel.ref_panel, NULL);

	lv_label_set_align(set_component_name_label, LV_LABEL_ALIGN_CENTER);
	lv_label_set_align(set_component_size_width_label, LV_LABEL_ALIGN_CENTER);
	lv_label_set_align(set_component_size_height_label, LV_LABEL_ALIGN_CENTER);
	lv_label_set_align(set_component_position_x_label, LV_LABEL_ALIGN_CENTER);
	lv_label_set_align(set_component_position_y_label, LV_LABEL_ALIGN_CENTER);

	lv_obj_set_width(set_component_name_label, property_panel.panel_width - 1);
	lv_obj_set_width(set_component_size_width_label, property_panel.panel_width - 1);
	lv_obj_set_width(set_component_size_height_label, property_panel.panel_width - 1);
	lv_obj_set_width(set_component_position_x_label, property_panel.panel_width - 1);
	lv_obj_set_width(set_component_position_y_label, property_panel.panel_width - 1);

	lv_label_set_text(set_component_name_label, "Name");
	lv_label_set_text(set_component_size_width_label, "Width");
	lv_label_set_text(set_component_size_height_label, "Height");
	lv_label_set_text(set_component_position_x_label, "Position X");
	lv_label_set_text(set_component_position_y_label, "Position Y");


	//set_component_name
	lv_ta_set_cursor_type(set_component_name,LV_CURSOR_NONE);
	lv_obj_set_width(set_component_name, property_panel.panel_width - 1);
	lv_ta_set_max_length(set_component_name,15);
	lv_ta_set_one_line(set_component_name, true);
	lv_ta_set_text(set_component_name, "");
	lv_obj_set_signal_func(set_component_name,lv_design_property_process_callback);
	lv_obj_set_pos(set_component_name, lv_obj_get_x(set_component_name), lv_obj_get_y(property_panel.ref_panel) );
	lv_obj_set_pos(set_component_name_label, lv_obj_get_x(set_component_name) + 10, lv_obj_get_y(set_component_name)-20);

	//set_component_size_width
	lv_ta_set_cursor_type(set_component_size_width,LV_CURSOR_NONE);
	lv_obj_set_width(set_component_size_width, property_panel.panel_width - 1);
	lv_ta_set_max_length(set_component_size_width,5);
	lv_ta_set_one_line(set_component_size_width, true);
	lv_ta_set_text(set_component_size_width, "");
	lv_obj_set_signal_func(set_component_size_width,lv_design_property_process_callback);
	lv_obj_set_pos(set_component_size_width, lv_obj_get_x(set_component_size_width), lv_obj_get_y(set_component_name)+ 70 );
	lv_obj_set_pos(set_component_size_width_label, lv_obj_get_x(set_component_size_width) + 10, lv_obj_get_y(set_component_size_width)-20);

	//set_component_size_height
	lv_ta_set_cursor_type(set_component_size_height,LV_CURSOR_NONE);
	lv_obj_set_width(set_component_size_height, property_panel.panel_width - 1);
	lv_ta_set_max_length(set_component_size_height,5);
	lv_ta_set_one_line(set_component_size_height, true);
	lv_ta_set_text(set_component_size_height, "");
	lv_obj_set_signal_func(set_component_size_height,lv_design_property_process_callback);
	lv_obj_set_pos(set_component_size_height, lv_obj_get_x(set_component_size_width), lv_obj_get_y(set_component_size_width)+ 70);
	lv_obj_set_pos(set_component_size_height_label, lv_obj_get_x(set_component_size_height) + 10, lv_obj_get_y(set_component_size_height)-20);

	//set_component_position_x
	lv_ta_set_cursor_type(set_component_position_x,LV_CURSOR_NONE);
	lv_obj_set_width(set_component_position_x, property_panel.panel_width - 1);
	lv_ta_set_max_length(set_component_position_x,5);
	lv_ta_set_one_line(set_component_position_x, true);
	lv_ta_set_text(set_component_position_x, "");
	lv_obj_set_signal_func(set_component_position_x,lv_design_property_process_callback);
	lv_obj_set_pos(set_component_position_x, lv_obj_get_x(set_component_size_width), lv_obj_get_y(set_component_size_height)+ 70);
	lv_obj_set_pos(set_component_position_x_label, lv_obj_get_x(set_component_position_x) + 10, lv_obj_get_y(set_component_position_x)-20);

	//set_component_position_y
	lv_ta_set_cursor_type(set_component_position_y,LV_CURSOR_NONE);
	lv_obj_set_width(set_component_position_y, property_panel.panel_width - 1);
	lv_ta_set_max_length(set_component_position_y,5);
	lv_ta_set_one_line(set_component_position_y, true);
	lv_ta_set_text(set_component_position_y, "");
	lv_obj_set_signal_func(set_component_position_y,lv_design_property_process_callback);
	lv_obj_set_pos(set_component_position_y, lv_obj_get_x(set_component_size_width), lv_obj_get_y(set_component_position_x )+ 70);
	lv_obj_set_pos(set_component_position_y_label, lv_obj_get_x(set_component_position_y) + 10, lv_obj_get_y(set_component_position_y)-20);

	area_position[FIRST_PROPERTY].attr_pos_x = lv_obj_get_x(set_component_name);
	area_position[FIRST_PROPERTY].attr_pos_y = lv_obj_get_y(set_component_name);

	area_position[SECOND_PROPERTY].attr_pos_y = lv_obj_get_x(set_component_size_width);
	area_position[SECOND_PROPERTY].attr_pos_y = lv_obj_get_y(set_component_size_width);

	area_position[THIRD_PROPERTY].attr_pos_y = lv_obj_get_x(set_component_size_height);
	area_position[THIRD_PROPERTY].attr_pos_y = lv_obj_get_y(set_component_size_height);

	area_position[FOURTH_PROPERTY].attr_pos_y = lv_obj_get_x(set_component_position_x);
	area_position[FOURTH_PROPERTY].attr_pos_y = lv_obj_get_y(set_component_position_x);

	area_position[FIFTH_PEOPERTY].attr_pos_y = lv_obj_get_x(set_component_position_y);
	area_position[FIFTH_PEOPERTY].attr_pos_y = lv_obj_get_y(set_component_position_y);

	lv_design_hidden_property(SELECTED_INIT,TRUE);

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

static void lv_design_draw_ui_preview()
{
//#define LV_HOR_RES          (800)
//#define LV_VER_RES          (480)
//	background_panel
	lv_obj_t * preview_button;
    lv_obj_t * preview_label;
    lv_obj_get_screen(component_panel.ref_panel);
//    printf
//    lv_btn_set_action(component_btn_info.main_button_info.ref_button, LV_BTN_ACTION_PR, lv_design_button_componet_press_callback);
    preview_button = lv_btn_create(background_panel, NULL);
    lv_btn_set_action(preview_button,LV_BTN_ACTION_PR, lv_design_pressed_preview_button_callback);
	lv_obj_set_size(preview_button, LV_HOR_RES/8 + 5, LV_VER_RES/16 + 5);
	lv_obj_align(preview_button,NULL,LV_ALIGN_IN_TOP_LEFT,component_panel.pos_x, 2);
	//lv_btn_set_toggle(preview_button,true);

    preview_label = lv_label_create(preview_button, NULL);
    lv_obj_align(preview_label,NULL,LV_ALIGN_CENTER,0,0);
    lv_label_set_text(preview_label, "preview");


}

lv_design_attribute_position_t* lv_design_get_attribute_position()
{
	return area_position;
}

lv_design_panel_info_t* lv_design_get_component_panel()
{
	return &component_panel;
}

void lv_design_set_screen_panel_press_state(unsigned char screen_panel_press_state)
{
	lv_obj_set_click(screen_panel.ref_panel, screen_panel_press_state);
}

void lv_design_launch_module()
{
//	lv_theme_set_current(lv_theme_night_init(210, NULL));
	lv_design_draw_background();
	lv_design_draw_screen();
	lv_design_draw_component();
	lv_design_draw_property();
	lv_design_draw_ui_preview();
}
