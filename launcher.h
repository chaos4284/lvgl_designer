/*
 * launcher.h
 *
 *  Created on: 2019. 1. 27.
 *      Author: root
 */

#ifndef LAUNCHER_H_
#define LAUNCHER_H_

typedef struct lv_design_panel_info
{
 unsigned int panel_width;
 unsigned int panel_height;
 unsigned int pos_x;
 unsigned int pos_y;
 unsigned int input_state;
 lv_obj_t* ref_panel;
}lv_design_panel_info_t;

enum select_component{
	SELECTED_INIT,
	SELECTED_SCREEN,
	SELECTED_BUTTON,
	SELECTED_LABEL,
	SELECTED_CHECKBOX,
};

extern void lv_design_init_button_component();
extern unsigned int lv_design_get_button_component_press_state();
extern void lv_design_set_button_component_press_state(unsigned int button_state);
extern lv_obj_t *lv_design_get_button_component_ref();


lv_res_t lv_design_screen_press_callback(lv_obj_t * btn, lv_signal_t sign, void * param);
void lv_design_launch_module();



#endif /* LAUNCHER_H_ */
