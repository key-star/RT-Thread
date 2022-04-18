/**
 ******************************************************************************
 * @file    lv_setting.c
 * @author  key-star
 * @version V1.0.0
 * @date    2022-03-30
 * @brief	设置
 ******************************************************************************
 * Change Logs:
 * Date           Author          Notes
 * 2022-03-30     key-star        First version
 ******************************************************************************
 * @attention
 *
 * Copyright (C) 2022-2022 key-star
 * All rights reserved
 *
 ******************************************************************************
 */

/*********************
 *      INCLUDES
 *********************/
#include "../lvgl/lvgl.h"
#include <msh.h>

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t *cont_setting;
static lv_obj_t *cont_setting_about;
static lv_obj_t *cont_setting_upgrade;

/**********************
 *       EXTERN
 **********************/
extern void lv_desktop_background(uint32_t delay);

/**********************
 *  STATIC PROTOTYPES
 **********************/
void lv_setting(void);
void lv_setting_about(void);
void lv_setting_upgrade(void);

static void event_handler_setting_about(lv_obj_t * obj, lv_event_t event);
static void event_handler_setting_upgrade(lv_obj_t * obj, lv_event_t event);
static void event_handler_setting_reboot(lv_obj_t * obj, lv_event_t event);
static void event_handler_setting_back_to_home(lv_obj_t * obj, lv_event_t event);
static void event_handler_setting_about_back(lv_obj_t * obj, lv_event_t event);

void lv_setting(void)
{
	//Write codes cont_setting
	cont_setting = lv_cont_create(lv_scr_act(), NULL);

	//Write style LV_CONT_PART_MAIN for cont_setting
	static lv_style_t style_cont_setting_main;
	lv_style_init(&style_cont_setting_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_main
	lv_style_set_radius(&style_cont_setting_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_cont_setting_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_cont_setting_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_cont_setting_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_cont_setting_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_cont_setting_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_cont_setting_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_cont_setting_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting, LV_CONT_PART_MAIN, &style_cont_setting_main);
	lv_obj_set_pos(cont_setting, 0, 0);
	lv_obj_set_size(cont_setting, 480, 800);
	lv_obj_set_click(cont_setting, false);
	lv_cont_set_layout(cont_setting, LV_LAYOUT_OFF);
	lv_cont_set_fit(cont_setting, LV_FIT_NONE);

    //Write codes cont_setting_label_1
	lv_obj_t *cont_setting_label_1 = lv_label_create(cont_setting, NULL);
	lv_label_set_text(cont_setting_label_1, "Setting");
	lv_label_set_long_mode(cont_setting_label_1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(cont_setting_label_1, LV_LABEL_ALIGN_LEFT);

	//Write style LV_LABEL_PART_MAIN for cont_setting_label_1
	static lv_style_t style_cont_setting_label_1_main;
	lv_style_init(&style_cont_setting_label_1_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_label_1_main
	lv_style_set_radius(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, &lv_font_montserrat_30);
	lv_style_set_text_letter_space(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_cont_setting_label_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_label_1, LV_LABEL_PART_MAIN, &style_cont_setting_label_1_main);
	lv_obj_set_pos(cont_setting_label_1, 20, 20);
	lv_obj_set_size(cont_setting_label_1, 150, 0);

	//Write codes cont_setting_list_1
	lv_obj_t *cont_setting_list_1 = lv_list_create(cont_setting, NULL);
	lv_list_set_edge_flash(cont_setting_list_1, true);

	//Write style LV_LIST_PART_BG for cont_setting_list_1
	static lv_style_t style_cont_setting_list_1_bg;
	lv_style_init(&style_cont_setting_list_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_list_1_bg
	lv_style_set_radius(&style_cont_setting_list_1_bg, LV_STATE_DEFAULT, 10);
	lv_style_set_border_color(&style_cont_setting_list_1_bg, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_cont_setting_list_1_bg, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_cont_setting_list_1_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_cont_setting_list_1_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_cont_setting_list_1_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(cont_setting_list_1, LV_LIST_PART_BG, &style_cont_setting_list_1_bg);

	//Write style LV_LIST_PART_SCROLLABLE for cont_setting_list_1
	static lv_style_t style_cont_setting_list_1_scrollable;
	lv_style_init(&style_cont_setting_list_1_scrollable);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_list_1_scrollable
	lv_style_set_radius(&style_cont_setting_list_1_scrollable, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_cont_setting_list_1_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_list_1_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_list_1_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_list_1_scrollable, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(cont_setting_list_1, LV_LIST_PART_SCROLLABLE, &style_cont_setting_list_1_scrollable);

	//Write style LV_BTN_PART_MAIN for cont_setting_list_1
	static lv_style_t style_cont_setting_list_1_main_child;
	lv_style_init(&style_cont_setting_list_1_main_child);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_list_1_main_child
	lv_style_set_radius(&style_cont_setting_list_1_main_child, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_cont_setting_list_1_main_child, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_list_1_main_child, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_list_1_main_child, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_list_1_main_child, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_cont_setting_list_1_main_child, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
	lv_obj_set_pos(cont_setting_list_1, 20, 80);
	lv_obj_set_size(cont_setting_list_1, 440, 84);
	lv_obj_t *cont_setting_list_1_btn;
	cont_setting_list_1_btn = lv_list_add_btn(cont_setting_list_1, LV_SYMBOL_WIFI, "WLAN");
	lv_obj_add_style(cont_setting_list_1_btn, LV_BTN_PART_MAIN, &style_cont_setting_list_1_main_child);
	cont_setting_list_1_btn = lv_list_add_btn(cont_setting_list_1, LV_SYMBOL_BLUETOOTH, "Bluetooth");
	lv_obj_add_style(cont_setting_list_1_btn, LV_BTN_PART_MAIN, &style_cont_setting_list_1_main_child);
    
	//Write codes cont_setting_list_2
	lv_obj_t *cont_setting_list_2 = lv_list_create(cont_setting, NULL);
	lv_list_set_edge_flash(cont_setting_list_2, true);

	//Write style LV_LIST_PART_BG for cont_setting_list_2
	static lv_style_t style_cont_setting_list_2_bg;
	lv_style_init(&style_cont_setting_list_2_bg);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_list_2_bg
	lv_style_set_radius(&style_cont_setting_list_2_bg, LV_STATE_DEFAULT, 10);
	lv_style_set_border_color(&style_cont_setting_list_2_bg, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_cont_setting_list_2_bg, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_left(&style_cont_setting_list_2_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_cont_setting_list_2_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_cont_setting_list_2_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(cont_setting_list_2, LV_LIST_PART_BG, &style_cont_setting_list_2_bg);

	//Write style LV_LIST_PART_SCROLLABLE for cont_setting_list_2
	static lv_style_t style_cont_setting_list_2_scrollable;
	lv_style_init(&style_cont_setting_list_2_scrollable);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_list_2_scrollable
	lv_style_set_radius(&style_cont_setting_list_2_scrollable, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_cont_setting_list_2_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_list_2_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_list_2_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_list_2_scrollable, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(cont_setting_list_2, LV_LIST_PART_SCROLLABLE, &style_cont_setting_list_2_scrollable);

	//Write style LV_BTN_PART_MAIN for cont_setting_list_2
	static lv_style_t style_cont_setting_list_2_main_child;
	lv_style_init(&style_cont_setting_list_2_main_child);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_list_2_main_child
	lv_style_set_radius(&style_cont_setting_list_2_main_child, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_cont_setting_list_2_main_child, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_list_2_main_child, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_list_2_main_child, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_list_2_main_child, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_cont_setting_list_2_main_child, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
	lv_obj_set_pos(cont_setting_list_2, 20, 190);
	lv_obj_set_size(cont_setting_list_2, 440, 123);
	lv_obj_t *cont_setting_list_2_btn;
	cont_setting_list_2_btn = lv_list_add_btn(cont_setting_list_2, LV_SYMBOL_SETTINGS, "About");
	lv_obj_add_style(cont_setting_list_2_btn, LV_BTN_PART_MAIN, &style_cont_setting_list_2_main_child);
	cont_setting_list_2_btn = lv_list_add_btn(cont_setting_list_2, LV_SYMBOL_DOWNLOAD, "Upgrade");
	lv_obj_add_style(cont_setting_list_2_btn, LV_BTN_PART_MAIN, &style_cont_setting_list_2_main_child);
	cont_setting_list_2_btn = lv_list_add_btn(cont_setting_list_2, LV_SYMBOL_POWER, "Reboot");
	lv_obj_add_style(cont_setting_list_2_btn, LV_BTN_PART_MAIN, &style_cont_setting_list_2_main_child);

	//Write codes cont_setting_btn_1
	lv_obj_t *cont_setting_btn_1 = lv_btn_create(cont_setting, NULL);

	//Write style LV_BTN_PART_MAIN for cont_setting_btn_1
	static lv_style_t style_cont_setting_btn_1_main;
	lv_style_init(&style_cont_setting_btn_1_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_btn_1_main
	lv_style_set_radius(&style_cont_setting_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_btn_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_cont_setting_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_cont_setting_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_cont_setting_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_cont_setting_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_cont_setting_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_btn_1, LV_BTN_PART_MAIN, &style_cont_setting_btn_1_main);
	lv_obj_set_pos(cont_setting_btn_1, 50, 93);
	lv_obj_set_size(cont_setting_btn_1, 380, 25);
	lv_obj_t *cont_setting_btn_1_label = lv_label_create(cont_setting_btn_1, NULL);
	lv_label_set_text(cont_setting_btn_1_label, LV_SYMBOL_RIGHT);
	lv_obj_set_style_local_text_color(cont_setting_btn_1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x7d, 0x7d, 0x7d));
	lv_obj_set_style_local_text_font(cont_setting_btn_1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_14);

	//Write codes cont_setting_btn_2
	lv_obj_t *cont_setting_btn_2 = lv_btn_create(cont_setting, NULL);

	//Write style LV_BTN_PART_MAIN for cont_setting_btn_2
	static lv_style_t style_cont_setting_btn_2_main;
	lv_style_init(&style_cont_setting_btn_2_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_btn_2_main
	lv_style_set_radius(&style_cont_setting_btn_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_btn_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_btn_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_cont_setting_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_cont_setting_btn_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_cont_setting_btn_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_cont_setting_btn_2_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_cont_setting_btn_2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_btn_2, LV_BTN_PART_MAIN, &style_cont_setting_btn_2_main);
	lv_obj_set_pos(cont_setting_btn_2, 50, 133);
	lv_obj_set_size(cont_setting_btn_2, 380, 25);
	lv_obj_t *cont_setting_btn_2_label = lv_label_create(cont_setting_btn_2, NULL);
	lv_label_set_text(cont_setting_btn_2_label, LV_SYMBOL_RIGHT);
	lv_obj_set_style_local_text_color(cont_setting_btn_2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x7d, 0x7d, 0x7d));
	lv_obj_set_style_local_text_font(cont_setting_btn_2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_14);

	//Write codes screen_btn_3
	lv_obj_t *cont_setting_btn_3 = lv_btn_create(cont_setting, NULL);

	//Write style LV_BTN_PART_MAIN for screen_btn_3
	static lv_style_t style_cont_setting_btn_3_main;
	lv_style_init(&style_cont_setting_btn_3_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_btn_3_main
	lv_style_set_radius(&style_cont_setting_btn_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_btn_3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_btn_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_cont_setting_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_cont_setting_btn_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_cont_setting_btn_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_cont_setting_btn_3_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_cont_setting_btn_3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_btn_3, LV_BTN_PART_MAIN, &style_cont_setting_btn_3_main);
	lv_obj_set_pos(cont_setting_btn_3, 50, 203);
	lv_obj_set_size(cont_setting_btn_3, 380, 25);
	lv_obj_t *cont_setting_btn_3_label = lv_label_create(cont_setting_btn_3, NULL);
	lv_label_set_text(cont_setting_btn_3_label, LV_SYMBOL_RIGHT);
	lv_obj_set_style_local_text_color(cont_setting_btn_3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x7d, 0x7d, 0x7d));
	lv_obj_set_style_local_text_font(cont_setting_btn_3_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_14);
    lv_obj_set_event_cb(cont_setting_btn_3, event_handler_setting_about);

	//Write codes cont_setting_btn_4
	lv_obj_t *cont_setting_btn_4 = lv_btn_create(cont_setting, NULL);

	//Write style LV_BTN_PART_MAIN for cont_setting_btn_4
	static lv_style_t style_cont_setting_btn_4_main;
	lv_style_init(&style_cont_setting_btn_4_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_btn_4_main
	lv_style_set_radius(&style_cont_setting_btn_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_btn_4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_btn_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_cont_setting_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_cont_setting_btn_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_cont_setting_btn_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_cont_setting_btn_4_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_cont_setting_btn_4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_btn_4, LV_BTN_PART_MAIN, &style_cont_setting_btn_4_main);
	lv_obj_set_pos(cont_setting_btn_4, 50, 243);
	lv_obj_set_size(cont_setting_btn_4, 380, 25);
	lv_obj_t *cont_setting_btn_4_label = lv_label_create(cont_setting_btn_4, NULL);
	lv_label_set_text(cont_setting_btn_4_label, LV_SYMBOL_RIGHT);
	lv_obj_set_style_local_text_color(cont_setting_btn_4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x7d, 0x7d, 0x7d));
	lv_obj_set_style_local_text_font(cont_setting_btn_4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_14);
    lv_obj_set_event_cb(cont_setting_btn_4, event_handler_setting_upgrade);

	//Write codes cont_setting_btn_5
	lv_obj_t *cont_setting_btn_5 = lv_btn_create(cont_setting, NULL);

	//Write style LV_BTN_PART_MAIN for cont_setting_btn_5
	static lv_style_t style_cont_setting_btn_5_main;
	lv_style_init(&style_cont_setting_btn_5_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_btn_5_main
	lv_style_set_radius(&style_cont_setting_btn_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_btn_5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_btn_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_cont_setting_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_cont_setting_btn_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_cont_setting_btn_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_cont_setting_btn_5_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_cont_setting_btn_5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_btn_5, LV_BTN_PART_MAIN, &style_cont_setting_btn_5_main);
	lv_obj_set_pos(cont_setting_btn_5, 50, 283);
	lv_obj_set_size(cont_setting_btn_5, 380, 25);
	lv_obj_t *cont_setting_btn_5_label = lv_label_create(cont_setting_btn_5, NULL);
	lv_label_set_text(cont_setting_btn_5_label, LV_SYMBOL_RIGHT);
	lv_obj_set_style_local_text_color(cont_setting_btn_5_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x7d, 0x7d, 0x7d));
	lv_obj_set_style_local_text_font(cont_setting_btn_5_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_14);
    lv_obj_set_event_cb(cont_setting_btn_5, event_handler_setting_reboot);

	//Write codes cont_setting_btn_6
	lv_obj_t *cont_setting_btn_6 = lv_btn_create(cont_setting, NULL);

	//Write style LV_BTN_PART_MAIN for cont_setting_btn_6
	static lv_style_t style_screen_btn_6_main;
	lv_style_init(&style_screen_btn_6_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_btn_6_main
	lv_style_set_radius(&style_screen_btn_6_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_btn_6_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_btn_6_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0x69, 0x69, 0x69));
	lv_style_set_border_width(&style_screen_btn_6_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_btn_6_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_screen_btn_6_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_screen_btn_6_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_btn_6, LV_BTN_PART_MAIN, &style_screen_btn_6_main);
	lv_obj_set_pos(cont_setting_btn_6, 430, 25);
	lv_obj_set_size(cont_setting_btn_6, 25, 25);
	lv_obj_t *cont_setting_btn_6_label = lv_label_create(cont_setting_btn_6, NULL);
	lv_label_set_text(cont_setting_btn_6_label, LV_SYMBOL_CLOSE);
	lv_obj_set_style_local_text_color(cont_setting_btn_6_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(cont_setting_btn_6_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_14);
    lv_obj_set_event_cb(cont_setting_btn_6, event_handler_setting_back_to_home);
}

/**********************************************************************
 * 功能描述： 关于本机的基本信息
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_setting_about(lv_obj_t * obj, lv_event_t event)
{
    switch (event)
	{
        case LV_EVENT_RELEASED:
        {
			lv_setting_about();
			msh_exec("free", rt_strlen("free"));
			lv_obj_del(cont_setting);
			msh_exec("free", rt_strlen("free"));
        }
        break;
        
        default:
            break;
	}
}

/**********************************************************************
 * 功能描述： 软件升级
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_setting_upgrade(lv_obj_t * obj, lv_event_t event)
{
    switch (event)
	{
        case LV_EVENT_RELEASED:
        {
            lv_setting_upgrade();
			lv_obj_del(cont_setting);
			msh_exec("ymodem_ota", rt_strlen("ymodem_ota"));
        }
        break;
        
        default:
            break;
	}
}

/**********************************************************************
 * 功能描述： 重启
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_setting_reboot(lv_obj_t * obj, lv_event_t event)
{
    switch (event)
	{
        case LV_EVENT_RELEASED:
        {
            msh_exec("reboot", rt_strlen("reboot"));
        }
        break;
        
        default:
            break;
	}
}

/**********************************************************************
 * 功能描述： 返回桌面
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_setting_back_to_home(lv_obj_t * obj, lv_event_t event)
{
    switch (event)
	{
        case LV_EVENT_RELEASED:
        {
			msh_exec("free", rt_strlen("free"));
            lv_desktop_background(0);
			//lv_obj_del(cont_setting);
			msh_exec("free", rt_strlen("free"));
        }
        break;
        
        default:
            break;
	}
}

void lv_setting_about(void)
{
	//Write codes cont_setting_about
	cont_setting_about = lv_cont_create(lv_scr_act(), NULL);

	//Write style LV_CONT_PART_MAIN for cont_setting_about
	static lv_style_t style_cont_setting_about_main;
	lv_style_init(&style_cont_setting_about_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_about_main
	lv_style_set_radius(&style_cont_setting_about_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_about_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_about_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_about_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_about_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_cont_setting_about_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_cont_setting_about_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_cont_setting_about_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_cont_setting_about_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_cont_setting_about_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_cont_setting_about_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_cont_setting_about_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_about, LV_CONT_PART_MAIN, &style_cont_setting_about_main);
	lv_obj_set_pos(cont_setting_about, 0, 0);
	lv_obj_set_size(cont_setting_about, 480, 800);
	lv_obj_set_click(cont_setting_about, false);
	lv_cont_set_layout(cont_setting_about, LV_LAYOUT_OFF);
	lv_cont_set_fit(cont_setting_about, LV_FIT_NONE);

	//Write codes cont_setting_about_label_1
	lv_obj_t *cont_setting_about_label_1 = lv_label_create(cont_setting_about, NULL);
	lv_label_set_text(cont_setting_about_label_1, "About");
	lv_label_set_long_mode(cont_setting_about_label_1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(cont_setting_about_label_1, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for cont_setting_about_label_1
	static lv_style_t style_cont_setting_about_label_1_main;
	lv_style_init(&style_cont_setting_about_label_1_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_about_label_1_main
	lv_style_set_radius(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, &lv_font_montserrat_30);
	lv_style_set_text_letter_space(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_cont_setting_about_label_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_about_label_1, LV_LABEL_PART_MAIN, &style_cont_setting_about_label_1_main);
	lv_obj_set_pos(cont_setting_about_label_1, 165, 20);
	lv_obj_set_size(cont_setting_about_label_1, 150, 0);

	//Write codes cont_setting_about_table_1
	lv_obj_t *cont_setting_about_table_1 = lv_table_create(cont_setting_about, NULL);

	//Write style LV_TABLE_PART_BG for cont_setting_about_table_1
	static lv_style_t style_cont_setting_about_table_1_bg;
	lv_style_init(&style_cont_setting_about_table_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_about_table_1_bg
	lv_style_set_bg_color(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, lv_color_make(0xae, 0xbf, 0xc5));
	lv_style_set_border_width(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, lv_color_make(0x39, 0x3c, 0x41));
	lv_style_set_text_decor(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, LV_TEXT_DECOR_NONE);
	lv_style_set_pad_left(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_cont_setting_about_table_1_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(cont_setting_about_table_1, LV_TABLE_PART_BG, &style_cont_setting_about_table_1_bg);

	//Write style LV_TABLE_PART_CELL1 for cont_setting_about_table_1
	static lv_style_t style_cont_setting_about_table_1_cell1;
	lv_style_init(&style_cont_setting_about_table_1_cell1);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_about_table_1_cell1
	lv_style_set_border_color(&style_cont_setting_about_table_1_cell1, LV_STATE_DEFAULT, lv_color_make(0xd5, 0xde, 0xe6));
	lv_style_set_border_width(&style_cont_setting_about_table_1_cell1, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(cont_setting_about_table_1, LV_TABLE_PART_CELL1, &style_cont_setting_about_table_1_cell1);
	lv_obj_set_pos(cont_setting_about_table_1, 20, 80);
	lv_table_set_col_cnt(cont_setting_about_table_1,2);
	lv_table_set_row_cnt(cont_setting_about_table_1,6);
	lv_table_set_cell_value(cont_setting_about_table_1,0,0,"Name");
	lv_table_set_cell_value(cont_setting_about_table_1,1,0,"Version");
	lv_table_set_cell_value(cont_setting_about_table_1,2,0,"Board");
	lv_table_set_cell_value(cont_setting_about_table_1,3,0,"Core");
	lv_table_set_cell_value(cont_setting_about_table_1,4,0,"Total ROM");
	lv_table_set_cell_value(cont_setting_about_table_1,5,0,"Free ROM");
	lv_table_set_cell_value(cont_setting_about_table_1,0,1,"Key star");
	lv_table_set_cell_value(cont_setting_about_table_1,1,1,"V1");
	lv_table_set_cell_value(cont_setting_about_table_1,2,1,"STM32F407ZG Core Board");
	lv_table_set_cell_value(cont_setting_about_table_1,3,1,"STM32F407ZG");
	lv_table_set_cell_value(cont_setting_about_table_1,4,1,"0");
	lv_table_set_cell_value(cont_setting_about_table_1,5,1,"0");
	lv_obj_set_style_local_pad_left(cont_setting_about_table_1, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 10);
	lv_obj_set_style_local_pad_right(cont_setting_about_table_1, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 10);
	lv_obj_set_style_local_pad_top(cont_setting_about_table_1, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 10);
	lv_obj_set_style_local_pad_bottom(cont_setting_about_table_1, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 10);

	//Write codes cont_setting_about_btn_1
	lv_obj_t *cont_setting_about_btn_1 = lv_btn_create(cont_setting_about, NULL);

	//Write style LV_BTN_PART_MAIN for cont_setting_about_btn_1
	static lv_style_t style_cont_setting_about_btn_1_main;
	lv_style_init(&style_cont_setting_about_btn_1_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_about_btn_1_main
	lv_style_set_radius(&style_cont_setting_about_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_about_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_about_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_about_btn_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_about_btn_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_cont_setting_about_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_cont_setting_about_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_cont_setting_about_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_cont_setting_about_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_cont_setting_about_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_about_btn_1, LV_BTN_PART_MAIN, &style_cont_setting_about_btn_1_main);
	lv_obj_set_pos(cont_setting_about_btn_1, 20, 20);
	lv_obj_set_size(cont_setting_about_btn_1, 30, 30);
	lv_obj_t *cont_setting_about_btn_1_label = lv_label_create(cont_setting_about_btn_1, NULL);
	lv_label_set_text(cont_setting_about_btn_1_label, LV_SYMBOL_LEFT);
	lv_obj_set_style_local_text_color(cont_setting_about_btn_1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x1e, 0xff));
	lv_obj_set_style_local_text_font(cont_setting_about_btn_1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_14);
    lv_obj_set_event_cb(cont_setting_about_btn_1, event_handler_setting_about_back);
}

/**********************************************************************
 * 功能描述： 返回上一级
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_setting_about_back(lv_obj_t * obj, lv_event_t event)
{
    switch (event)
	{
        case LV_EVENT_RELEASED:
        {
            lv_setting();
			msh_exec("free", rt_strlen("free"));
			lv_obj_del(cont_setting_about);
			msh_exec("free", rt_strlen("free"));
        }
        break;
        
        default:
            break;
	}
}

void lv_setting_upgrade(void)
{
	//Write codes cont_setting_upgrade
	cont_setting_upgrade = lv_cont_create(lv_scr_act(), NULL);

	//Write style LV_CONT_PART_MAIN for cont_setting_upgrade
	static lv_style_t style_cont_setting_upgrade_main;
	lv_style_init(&style_cont_setting_upgrade_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_upgrade_main
	lv_style_set_radius(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_cont_setting_upgrade_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_upgrade, LV_CONT_PART_MAIN, &style_cont_setting_upgrade_main);
	lv_obj_set_pos(cont_setting_upgrade, 0, 0);
	lv_obj_set_size(cont_setting_upgrade, 480, 800);
	lv_obj_set_click(cont_setting_upgrade, false);
	lv_cont_set_layout(cont_setting_upgrade, LV_LAYOUT_OFF);
	lv_cont_set_fit(cont_setting_upgrade, LV_FIT_NONE);

	//Write codes cont_setting_upgrade_slider_1
	lv_obj_t *cont_setting_upgrade_slider_1 = lv_slider_create(cont_setting_upgrade, NULL);

	//Write style LV_SLIDER_PART_INDIC for cont_setting_upgrade_slider_1
	static lv_style_t style_cont_setting_upgrade_slider_1_indic;
	lv_style_init(&style_cont_setting_upgrade_slider_1_indic);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_upgrade_slider_1_indic
	lv_style_set_radius(&style_cont_setting_upgrade_slider_1_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_cont_setting_upgrade_slider_1_indic, LV_STATE_DEFAULT, lv_color_make(0x03, 0xe8, 0xfc));
	lv_style_set_bg_grad_color(&style_cont_setting_upgrade_slider_1_indic, LV_STATE_DEFAULT, lv_color_make(0x02, 0xa2, 0xb1));
	lv_style_set_bg_grad_dir(&style_cont_setting_upgrade_slider_1_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_upgrade_slider_1_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(cont_setting_upgrade_slider_1, LV_SLIDER_PART_INDIC, &style_cont_setting_upgrade_slider_1_indic);

	//Write style LV_SLIDER_PART_BG for cont_setting_upgrade_slider_1
	static lv_style_t style_cont_setting_upgrade_slider_1_bg;
	lv_style_init(&style_cont_setting_upgrade_slider_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_upgrade_slider_1_bg
	lv_style_set_radius(&style_cont_setting_upgrade_slider_1_bg, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_cont_setting_upgrade_slider_1_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_cont_setting_upgrade_slider_1_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_dir(&style_cont_setting_upgrade_slider_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_upgrade_slider_1_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_cont_setting_upgrade_slider_1_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_cont_setting_upgrade_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_cont_setting_upgrade_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_cont_setting_upgrade_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_cont_setting_upgrade_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_cont_setting_upgrade_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_upgrade_slider_1, LV_SLIDER_PART_BG, &style_cont_setting_upgrade_slider_1_bg);
	lv_obj_set_pos(cont_setting_upgrade_slider_1, 60, 400);
	lv_obj_set_size(cont_setting_upgrade_slider_1, 360, 8);
	lv_slider_set_range(cont_setting_upgrade_slider_1,0, 100);
	lv_slider_set_value(cont_setting_upgrade_slider_1,10,false);

	//Write codes cont_setting_upgrade_label_1
	lv_obj_t *cont_setting_upgrade_label_1 = lv_label_create(cont_setting_upgrade, NULL);
	lv_label_set_text(cont_setting_upgrade_label_1, "upgrading,please do not power off");
	lv_label_set_long_mode(cont_setting_upgrade_label_1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(cont_setting_upgrade_label_1, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for cont_setting_upgrade_label_1
	static lv_style_t style_cont_setting_upgrade_label_1_main;
	lv_style_init(&style_cont_setting_upgrade_label_1_main);

	//Write style state: LV_STATE_DEFAULT for style_cont_setting_upgrade_label_1_main
	lv_style_set_radius(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, &lv_font_montserrat_14);
	lv_style_set_text_letter_space(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_cont_setting_upgrade_label_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(cont_setting_upgrade_label_1, LV_LABEL_PART_MAIN, &style_cont_setting_upgrade_label_1_main);
	lv_obj_set_pos(cont_setting_upgrade_label_1, 90, 418);
	lv_obj_set_size(cont_setting_upgrade_label_1, 300, 0);
}
