/*
 * button_management.h
 *
 *  Created on: 2019. 1. 26.
 *      Author: root
 */

#ifndef BUTTON_MANAGEMENT_H_
#define BUTTON_MANAGEMENT_H_
#include "main.h"
#include "launcher.h"
typedef struct lv_deisgn_button_info
{
	unsigned int pos_x;
	unsigned int pos_y;
	unsigned int width;
	unsigned int height;
	lv_obj_t	*ref_button;
	lv_obj_t 	*ref_label;
	struct lv_deisgn_button_info *next;

}lv_deisgn_button_info_t;

typedef struct lv_design_button_list
{
	lv_deisgn_button_info_t *user_btn_list;
	lv_deisgn_button_info_t main_button_info;
	lv_design_panel_info_t *parent_panel;
	unsigned int main_button_pressed;
	unsigned int btn_count;
}lv_design_button_list_t;

lv_design_button_list_t* lv_design_get_button_info();
lv_obj_t* lv_design_get_button_component_ref();
unsigned int lv_design_get_button_component_press_state();
void lv_design_set_button_component_press_state(unsigned int button_state);


extern lv_design_panel_info_t* lv_design_get_component_panel();

#endif /* BUTTON_MANAGEMENT_H_ */
