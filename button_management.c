
 /* button_management.c
 *
 *  Created on: 2019. 1. 26.
 *      Author: root
*/

#include "lv_conf.h"
#include "lvgl/lvgl.h"
#include "launcher.h"
#include "button_management.h"

extern lv_design_attribute_position_t* lv_design_get_attribute_position(void);
extern	void lv_design_set_current_selected_component(unsigned char selected_component);
extern void lv_design_display_property_window(int attribute , lv_design_attribute_position_t *pos, char* content);
extern void lv_design_hidden_property(int component,bool hidden_flag);

static lv_res_t lv_design_button_componet_press_callback(lv_obj_t* btn);
static lv_design_button_list_t component_btn_info;
static unsigned int current_btn_id = 0;


void lv_design_init_button_component()
{
	component_btn_info.parent_panel = lv_design_get_component_panel();
	component_btn_info.main_button_info.ref_button = lv_btn_create(component_btn_info.parent_panel->ref_panel, NULL);
	component_btn_info.main_button_info.width = component_btn_info.parent_panel->panel_width;
	component_btn_info.main_button_info.height = 40;
	component_btn_info.main_button_info.pos_x = 0;
	component_btn_info.main_button_info.pos_y = 0;
	component_btn_info.user_btn_list = NULL;
	component_btn_info.btn_count = 0;

	lv_obj_set_size(component_btn_info.main_button_info.ref_button, component_btn_info.main_button_info.width, component_btn_info.main_button_info.height);
	lv_obj_align(component_btn_info.main_button_info.ref_button,NULL,LV_ALIGN_IN_TOP_LEFT,component_btn_info.main_button_info.pos_x ,component_btn_info.main_button_info.pos_y);
	lv_btn_set_toggle(component_btn_info.main_button_info.ref_button,true);
	lv_btn_set_action(component_btn_info.main_button_info.ref_button, LV_BTN_ACTION_PR, lv_design_button_componet_press_callback);
	component_btn_info.main_button_info.ref_label = lv_label_create(component_btn_info.main_button_info.ref_button, NULL);
	lv_obj_align(component_btn_info.main_button_info.ref_label,NULL,LV_ALIGN_CENTER,0,0);
	lv_label_set_text(component_btn_info.main_button_info.ref_label, "Button");
}

void lv_design_insert_user_button(lv_deisgn_button_info_t *new_button)
{
	lv_deisgn_button_info_t *temp_btn_list;

	if(component_btn_info.user_btn_list == NULL)
	{
		component_btn_info.user_btn_list = (lv_deisgn_button_info_t*)malloc(sizeof(lv_deisgn_button_info_t));
		memcpy(component_btn_info.user_btn_list ,new_button,sizeof(lv_deisgn_button_info_t));
		component_btn_info.user_btn_list->next = NULL;

	}
	else
	{
		temp_btn_list = component_btn_info.user_btn_list;
		while(temp_btn_list->next != NULL)
		{
			temp_btn_list = temp_btn_list->next;
		}
		
		temp_btn_list->next = (lv_deisgn_button_info_t*)malloc(sizeof(lv_deisgn_button_info_t));
		memcpy(temp_btn_list->next,new_button,sizeof(lv_deisgn_button_info_t));
		temp_btn_list->next->next = NULL;

	}
	
	temp_btn_list = component_btn_info.user_btn_list;
	for(int i = 0 ; i<component_btn_info.btn_count;i++ )
	{
		temp_btn_list = temp_btn_list->next;
	}

}

lv_deisgn_button_info_t *lv_design_get_button_by_id(unsigned int btn_id)
{
	lv_deisgn_button_info_t *ret_value = (lv_deisgn_button_info_t*)malloc(sizeof(lv_deisgn_button_info_t));
	lv_deisgn_button_info_t *temp_btn_list = NULL;
	temp_btn_list = component_btn_info.user_btn_list;

	if(temp_btn_list->next == NULL)
	{
		if(temp_btn_list->ref_button->free_num == btn_id)
		{
			ret_value = temp_btn_list;
		}
		else
		{
			ret_value = NULL;
		}

	}
	else
	{
		while(temp_btn_list != NULL)
		{
			if(temp_btn_list->ref_button->free_num == btn_id)
			{
				ret_value = temp_btn_list;
				break;
			}
			else
			{
				temp_btn_list = temp_btn_list->next;
			}
			ret_value = NULL;
		}

	}


	return ret_value;
}

lv_design_button_list_t* lv_design_get_button_info()
{
	return  &component_btn_info;
}

unsigned int lv_design_get_button_component_press_state()
{
	return component_btn_info.main_button_pressed;
}

void lv_design_set_button_component_press_state(unsigned int btn_press_state)
{
	component_btn_info.main_button_pressed = btn_press_state;
}

lv_obj_t* lv_design_get_button_component_ref()
{
	return component_btn_info.main_button_info.ref_button;
}

static lv_res_t lv_design_button_componet_press_callback(lv_obj_t* btn)
{

	if(component_btn_info.main_button_pressed  == FALSE)
	{
		component_btn_info.main_button_pressed = TRUE;
	}
	else
	{
		component_btn_info.main_button_pressed = FALSE;
	}
    return LV_RES_OK;
}
int lv_design_get_selected_button_id()
{
	return current_btn_id;
}

lv_res_t lv_design_draw_property_of_user_button(lv_obj_t* btn)
{
	lv_res_t res = 0;

	char data[100];
	lv_design_attribute_position_t *btn_attr_pos;
	lv_deisgn_button_info_t *get_user_btn_content;// = (lv_deisgn_button_info_t*)malloc(sizeof(lv_deisgn_button_info_t));

	current_btn_id = btn->free_num;
	get_user_btn_content = lv_design_get_button_by_id(current_btn_id);

	if(get_user_btn_content == NULL)
	{
		return 0;
	}
	else
	{
		;
	}
	btn_attr_pos = lv_design_get_attribute_position();

	sprintf(data,"%s",lv_label_get_text(get_user_btn_content->ref_label));
	lv_design_display_property_window(SELECTED_NAME , &btn_attr_pos[FIRST_PROPERTY], data);
	sprintf(data,"%d",get_user_btn_content->width);
	lv_design_display_property_window(SELECTED_WIDTH , &btn_attr_pos[SECOND_PROPERTY], data);
	sprintf(data,"%d",get_user_btn_content->height);
	lv_design_display_property_window(SELECTED_HEIGHT , &btn_attr_pos[THIRD_PROPERTY], data);
	sprintf(data,"%d",get_user_btn_content->pos_x);
	lv_design_display_property_window(SELECTED_POS_X , &btn_attr_pos[FOURTH_PROPERTY], data);
	sprintf(data,"%d",get_user_btn_content->pos_y);
	lv_design_display_property_window(SELECTED_POS_Y , &btn_attr_pos[FIFTH_PEOPERTY], data);

	lv_design_hidden_property(SELECTED_BUTTON,TRUE);
	lv_design_hidden_property(SELECTED_BUTTON,FALSE);
	return res;
}

lv_res_t lv_design_manage_position_of_user_button_callback(lv_obj_t * btn, lv_signal_t sign, void * param)
{
	lv_res_t res = 0;
	lv_deisgn_button_info_t *get_user_btn_content;// = (lv_deisgn_button_info_t*)malloc(sizeof(lv_deisgn_button_info_t));
	current_btn_id = btn->free_num;
	get_user_btn_content = lv_design_get_button_by_id(current_btn_id);

	if(sign == LV_SIGNAL_PRESSED)
	{
		lv_design_draw_property_of_user_button(get_user_btn_content->ref_button);
		lv_design_set_current_selected_component(SELECTED_BUTTON);
	}
	else if(sign == LV_SIGNAL_DRAG_END)
	{
		get_user_btn_content->pos_x =lv_obj_get_x(get_user_btn_content->ref_button);
		get_user_btn_content->pos_y =lv_obj_get_y(get_user_btn_content->ref_button);

		lv_obj_set_pos(get_user_btn_content->ref_button, get_user_btn_content->pos_x, get_user_btn_content->pos_y);
	}

	return res;
}

