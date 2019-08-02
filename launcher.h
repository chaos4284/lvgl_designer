/*
 * launcher.h
 *
 *  Created on: 2019. 1. 27.
 *      Author: root
 */

#ifndef LAUNCHER_H_
#define LAUNCHER_H_

#define PROPERTY_COUNT	5

typedef struct lv_design_panel_info
{
 unsigned int panel_width;
 unsigned int panel_height;
 unsigned int pos_x;
 unsigned int pos_y;
 unsigned int input_state;
 lv_obj_t* ref_panel;
}lv_design_panel_info_t;

typedef struct lv_design_attribute_position
{
 unsigned int attr_pos_x;
 unsigned int attr_pos_y;

}lv_design_attribute_position_t;

enum select_component{
	SELECTED_INIT,
	SELECTED_SCREEN,
	SELECTED_BUTTON,
	SELECTED_LABEL,
	SELECTED_CHECKBOX,
};

enum select_property{
	SELECTED_NAME,
	SELECTED_WIDTH,
	SELECTED_HEIGHT,
	SELECTED_POS_X,
	SELECTED_POS_Y,
};

enum order_location{
	FIRST_PROPERTY,
	SECOND_PROPERTY,
	THIRD_PROPERTY,
	FOURTH_PROPERTY,
	FIFTH_PEOPERTY,
};
#define LV_GROUP_KEY_DEL            127     /*0x7F*/
#define LV_GROUP_KEY_BACKSPACE      8       /*0x08*/
#define LV_GROUP_KEY_ENTER          10      /*0x0A, '\n'*/

extern void lv_design_init_button_component();
extern unsigned int lv_design_get_button_component_press_state();
extern void lv_design_set_button_component_press_state(unsigned int button_state);
extern lv_obj_t *lv_design_get_button_component_ref();
extern lv_res_t lv_design_manage_position_of_user_button_callback(lv_obj_t * btn, lv_signal_t sign, void * param);

lv_res_t lv_design_screen_press_callback(lv_obj_t * btn, lv_signal_t sign, void * param);
void lv_design_launch_module();



#endif /* LAUNCHER_H_ */
