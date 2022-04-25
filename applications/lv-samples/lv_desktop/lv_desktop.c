/**
 ******************************************************************************
 * @file    lv_desktop.c
 * @author  key-star
 * @version V1.0.0
 * @date    2022-03-30
 * @brief	初始化桌面
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
#include "lv_desktop.h"
#include <msh.h>

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t *bg_top;			// 背景
static lv_obj_t *tabview_desktop;	// 页签
static uint16_t tabview_desktop_id;	// 记录页签当前展示的页面

/**********************
 *       EXTERN
 **********************/
// extern void lv_100ask_game_2048(void);					// 2048游戏
extern void lv_setting(void);          // 关于我们
// extern void lv_100ask_stm32_tool_calc(void);            // 计算器
// extern void lv_100ask_stm32_game_snake(void);           // 贪吃蛇游戏
// extern void lv_100ask_stm32_tool_clock(void);           // 时钟
// extern void lv_100ask_stm32_tool_regbit(void);          // 寄存器位查看计算工具
// extern void lv_100ask_stm32_tool_qrcode(void);          // 创建二维码
// extern void lv_100ask_stm32_music_player(void);         // 音乐播放器
// extern void lv_100ask_stm32_tool_setting(void);         // 系统设置
// extern void lv_100ask_stm32_tool_humiture(void);        // 温湿度检测
// extern void lv_100ask_stm32_tool_widget_test(void);     // 部件测试
// extern void lv_100ask_stm32_tool_file_browser(void);    // 文件浏览器
// extern void lv_100ask_boot_animation(uint32_t delay);   // 开机动画

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void event_handler_setting(lv_obj_t * obj, lv_event_t event);					// 打开关于我们应用事件处理函数
// static void event_handler_stm32_demo_game_2048(lv_obj_t * obj, lv_event_t event);				// 打开2048游戏应用事件处理函数事件处理函数
// static void event_handler_stm32_demo_tools_calc(lv_obj_t * obj, lv_event_t event);      		// 打开计算器应用事件处理函数
// static void event_handler_stm32_demo_game_snake(lv_obj_t * obj, lv_event_t event);			    // 打开贪吃蛇游戏应用事件处理函数
// static void event_handler_stm32_demo_tools_clock(lv_obj_t * obj, lv_event_t event);			    // 打开时钟应用事件处理函数
// static void event_handler_stm32_demo_tools_regbit(lv_obj_t * obj, lv_event_t event);   			// 打开寄存器位查看计算工具应用事件处理函数
// static void event_handler_stm32_demo_tools_qrcode(lv_obj_t * obj, lv_event_t event);   			// 打开创建二维码应用事件处理函数
// static void event_handler_stm32_demo_music_player(lv_obj_t * obj, lv_event_t event); 			// 打开音乐播放器应用事件处理函数
// static void event_handler_stm32_demo_tools_humiture(lv_obj_t * obj, lv_event_t event);			// 打开温湿度应用事件处理函数
// static void event_handler_stm32_demo_tools_settings(lv_obj_t * obj, lv_event_t event);			// 打开系统设置应用事件处理函数
// static void event_handler_stm32_demo_tools_widget_test(lv_obj_t * obj, lv_event_t event);		// 打开ADC、LED、BEEP测试应用事件处理函数
// static void event_handler_stm32_demo_tools_file_browser(lv_obj_t * obj, lv_event_t event); 		// 打开文件浏览器应用事件处理函数

/* 桌标图标声明 */
// LV_IMG_DECLARE(img_lv_100ask_icon_2048);		// 00 LV_100ASK_MENU_ITEM_COUNT
LV_IMG_DECLARE(img_lv_100ask_icon_about_us);	// 01
// LV_IMG_DECLARE(img_lv_100ask_icon_setting);	    // 02
// LV_IMG_DECLARE(img_lv_100ask_icon_data);		// 03
// LV_IMG_DECLARE(img_lv_100ask_icon_floder);		// 04
// LV_IMG_DECLARE(img_lv_100ask_icon_music);		// 05
// LV_IMG_DECLARE(img_lv_100ask_icon_QRcode);  	// 06
// LV_IMG_DECLARE(img_lv_100ask_icon_snake);		// 07
// LV_IMG_DECLARE(img_lv_100ask_icon_humiture);	// 08
// LV_IMG_DECLARE(img_lv_100ask_icon_regbit);		// 09
// LV_IMG_DECLARE(img_lv_100ask_icon_calc);		// 10
// LV_IMG_DECLARE(img_lv_100ask_icon_widgets);   	// 11

/* 桌标图标数组 */
static const lv_img_dsc_t *app_icon[] = \
{ \
    &img_lv_100ask_icon_about_us
    // &img_lv_100ask_icon_floder,	 &img_lv_100ask_icon_data, 	   &img_lv_100ask_icon_QRcode,	  &img_lv_100ask_icon_about_us, \
    // &img_lv_100ask_icon_humiture,  &img_lv_100ask_icon_2048,	   &img_lv_100ask_icon_music,	  &img_lv_100ask_icon_snake, \
    // &img_lv_100ask_icon_calc,      &img_lv_100ask_icon_regbit,   \
    // &img_lv_100ask_icon_setting, \
    // &img_lv_100ask_icon_widgets
};

/* 回调函数指针数组*/ 
static void (*lv_100ask_event_cb[])(lv_obj_t * obj, lv_event_t e) = \
{ \
    event_handler_setting
    /* event_handler_stm32_demo_tools_file_browser, event_handler_stm32_demo_tools_clock, event_handler_stm32_demo_tools_qrcode,  event_handler_stm32_demo_about, \
    event_handler_stm32_demo_tools_humiture,     event_handler_stm32_demo_game_2048,   event_handler_stm32_demo_music_player,  event_handler_stm32_demo_game_snake, \
    event_handler_stm32_demo_tools_calc,         event_handler_stm32_demo_tools_regbit, \
    event_handler_stm32_demo_tools_settings, \
    event_handler_stm32_demo_tools_widget_test \ */
};

/* 应用图标名称 */ 
static const char * app_name[] = \
{ \
    "Setting"
    // "file",     "time",    "QRcode",  "aboutus", \
    // "humiture", "2048",    "music",  "snake", \
    // "calc",     "regbit", \
    // "camera",  \
    // "test"
};

/**********************************************************************
 * 功能描述： 桌面背景初始化
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
void lv_desktop_background(uint32_t delay)
{
	lv_obj_clean(lv_scr_act()); 					// 确保屏幕无残留
    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);

    /* 桌面背景 */
	bg_top = lv_cont_create(lv_scr_act(), NULL);
	//Write style LV_CONT_PART_MAIN for bg_top
	static lv_style_t style_bg_top_main;
	lv_style_init(&style_bg_top_main);

	//Write style state: LV_STATE_DEFAULT for style_bg_top_main
	lv_style_set_radius(&style_bg_top_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_bg_top_main, LV_STATE_DEFAULT, lv_color_make(0x4a, 0xb2, 0x41));
	lv_style_set_bg_grad_color(&style_bg_top_main, LV_STATE_DEFAULT, lv_color_make(0x4a, 0xb2, 0x41));
	lv_style_set_bg_grad_dir(&style_bg_top_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_bg_top_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_bg_top_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_bg_top_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_bg_top_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_bg_top_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_bg_top_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_bg_top_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_bg_top_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(bg_top, LV_CONT_PART_MAIN, &style_bg_top_main);
	lv_obj_set_pos(bg_top, 0, 0);
	lv_obj_set_size(bg_top, LV_HOR_RES, LV_VER_RES);
	lv_obj_set_click(bg_top, false);
	lv_cont_set_layout(bg_top, LV_LAYOUT_OFF);
	lv_cont_set_fit(bg_top, LV_FIT_NONE);

	/* 图标 电池*/
    lv_obj_t * label_state = lv_label_create(bg_top, NULL);
	lv_obj_set_style_local_text_color(label_state, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);    		// 设置颜色
    lv_label_set_text(label_state, LV_SYMBOL_BATTERY_FULL);
    lv_obj_align_origo(label_state, NULL, LV_ALIGN_IN_TOP_RIGHT, -(15*1), 10);
    lv_obj_fade_in(label_state, 0, delay);

	/* 图标 时间 */
    label_state = lv_label_create(bg_top, NULL);
	lv_obj_set_style_local_text_color(label_state, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);    		// 设置颜色
    lv_label_set_text(label_state, "9:41");
    lv_obj_set_style_local_text_font(label_state, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_14);	// 设置文字大小
    lv_obj_align_origo(label_state, NULL, LV_ALIGN_IN_TOP_MID, 0, lv_obj_get_height(label_state)/2);
    lv_obj_fade_in(label_state, 0, delay);

	tabview_desktop_id = 1; 								    // 默认为主页面位置
    
    void lv_home_init(uint32_t delay);
    lv_home_init(delay + LV_100ASK_HOME_OPEN_TIME);             // 初始化主界面
}

/**********************************************************************
 * 功能描述： 主界面初始化
 * 输入参数： 动画延时时间
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
void lv_home_init(uint32_t delay)
{
    /* 创建三个页签作为菜单容器 */
    tabview_desktop = lv_tabview_create(lv_scr_act(), NULL);
    lv_obj_set_style_local_bg_opa(tabview_desktop, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_0);       // 设置背景透明度
    lv_tabview_set_btns_pos(tabview_desktop, LV_TABVIEW_TAB_POS_NONE);
    lv_tabview_add_tab(tabview_desktop, "left_desktop");  // 0
    lv_tabview_add_tab(tabview_desktop, "main_desktop");  // 1
    lv_tabview_add_tab(tabview_desktop, "right_desktop"); // 2
    lv_tabview_set_anim_time(tabview_desktop, 0);         // 动画时间
    lv_tabview_set_tab_act(tabview_desktop, tabview_desktop_id, LV_ANIM_OFF);
    lv_obj_fade_in(tabview_desktop, 0 , (delay + LV_100ASK_HOME_OPEN_TIME));

   /* 左菜单指示 */
    lv_obj_t * left_round1 = lv_cont_create(lv_tabview_get_tab(tabview_desktop, 0), NULL);         		// 中间
    lv_obj_set_style_local_bg_opa(left_round1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_80);          // 设置背景透明度
    lv_obj_set_style_local_radius(left_round1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 100);                // 设置圆角
    lv_obj_set_style_local_bg_color(left_round1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);   // 设置颜色
    lv_obj_set_size(left_round1, 8, 8);
    lv_obj_align(left_round1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));

    lv_obj_t * left_round2 = lv_cont_create(lv_tabview_get_tab(tabview_desktop, 0), left_round1);  		// 右边
    lv_obj_set_style_local_bg_opa(left_round2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_80);          // 设置背景透明度
    lv_obj_set_style_local_radius(left_round2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 100);                // 设置圆角
    lv_obj_set_style_local_bg_color(left_round2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);   // 设置颜色
    lv_obj_align(left_round2, NULL, LV_ALIGN_IN_BOTTOM_MID, 20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));

    lv_obj_t * left_round3 = lv_cont_create(lv_tabview_get_tab(tabview_desktop, 0), left_round1);  		// 左边
    lv_obj_set_style_local_bg_opa(left_round3, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_30);          // 设置背景透明度
    lv_obj_set_style_local_radius(left_round3, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 100);                // 设置圆角
    lv_obj_set_style_local_bg_color(left_round3, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);   // 设置颜色
    lv_obj_align(left_round3, NULL, LV_ALIGN_IN_BOTTOM_MID, -20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));


    /* 主菜单指示 */
    lv_obj_t * main_round1 = lv_cont_create(lv_tabview_get_tab(tabview_desktop, 1), NULL);         		// 中间
    lv_obj_set_style_local_bg_opa(main_round1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_30);          // 设置背景透明度
    lv_obj_set_style_local_radius(main_round1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 100);                // 设置圆角
    lv_obj_set_style_local_bg_color(main_round1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);   // 设置颜色
    lv_obj_set_size(main_round1, 8, 8);
    lv_obj_align(main_round1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));
    lv_obj_fade_in(main_round1, 0 , (delay + LV_100ASK_HOME_OPEN_TIME));

    lv_obj_t * main_round2 = lv_cont_create(lv_tabview_get_tab(tabview_desktop, 1), main_round1); 		// 右边
    lv_obj_set_style_local_bg_opa(main_round2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_80);          // 设置背景透明度
    lv_obj_set_style_local_radius(main_round2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 100);                // 设置圆角
    lv_obj_set_style_local_bg_color(main_round2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);   // 设置颜色
    lv_obj_align(main_round2, NULL, LV_ALIGN_IN_BOTTOM_MID, 20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));
    lv_obj_fade_in(main_round2, 0 , (delay + LV_100ASK_HOME_OPEN_TIME));

    lv_obj_t * main_round3 = lv_cont_create(lv_tabview_get_tab(tabview_desktop, 1), main_round1);  		// 左边
    lv_obj_set_style_local_bg_opa(main_round3, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_80);          // 设置背景透明度
    lv_obj_set_style_local_radius(main_round3, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 100);                // 设置圆角
    lv_obj_set_style_local_bg_color(main_round3, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);   // 设置颜色
    lv_obj_align(main_round3, NULL, LV_ALIGN_IN_BOTTOM_MID, -20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));
    lv_obj_fade_in(main_round3, 0 , (delay + LV_100ASK_HOME_OPEN_TIME));


    /* 右菜单指示 */
    lv_obj_t * right_round1 = lv_cont_create(lv_tabview_get_tab(tabview_desktop, 2), NULL);         	// 中间
    lv_obj_set_style_local_bg_opa(right_round1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_80);         // 设置背景透明度
    lv_obj_set_style_local_radius(right_round1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 100);               // 设置圆角
    lv_obj_set_style_local_bg_color(right_round1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);  // 设置颜色
    lv_obj_set_size(right_round1, 8, 8);
    lv_obj_align(right_round1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));

    lv_obj_t * right_round2 = lv_cont_create(lv_tabview_get_tab(tabview_desktop, 2), right_round1);  	// 右边
    lv_obj_set_style_local_bg_opa(right_round2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_30);         // 设置背景透明度
    lv_obj_set_style_local_radius(right_round2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 100);               // 设置圆角
    lv_obj_set_style_local_bg_color(right_round2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);  // 设置颜色
    lv_obj_align(right_round2, NULL, LV_ALIGN_IN_BOTTOM_MID, 20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));

    lv_obj_t * right_round3 = lv_cont_create(lv_tabview_get_tab(tabview_desktop, 2), right_round1);  	// 左边
    lv_obj_set_style_local_bg_opa(right_round3, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_80);         // 设置背景透明度
    lv_obj_set_style_local_radius(right_round3, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 100);               // 设置圆角
    lv_obj_set_style_local_bg_color(right_round3, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);  // 设置颜色
    lv_obj_align(right_round3, NULL, LV_ALIGN_IN_BOTTOM_MID, -20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));
	
    /* 创建主菜单 */
	lv_obj_t * label_app_name;  // app图标下方的文字
	lv_obj_t * obj_menu_item;	// 用于遍历初始化app图标的指针
	uint8_t row_count = 0; 		// 行
	uint8_t col_count = 0; 		// 列
    
    // 列
    lv_coord_t col_space = ((((LV_100ASK_BOTTOM_MENU_W - (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * LV_100ASK_BOTTOM_MENU_ITEM_COUNT)) / 5) * (col_count + 1)) + (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * col_count));
    
	// 行
    lv_coord_t row_space = ((((LV_100ASK_BOTTOM_MENU_W - (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * LV_100ASK_BOTTOM_MENU_ITEM_COUNT)) / 5) * (row_count + 1)) + (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * row_count));
    
    for (int i = 0; i < LV_100ASK_MENU_ITEM_COUNT; i++)
    {
        if ((i >= 0) && (i < 10))  		// 主菜单
        {
            obj_menu_item = lv_img_create(lv_tabview_get_tab(tabview_desktop, 1), NULL);
            label_app_name = lv_label_create(lv_tabview_get_tab(tabview_desktop, 1), NULL);
        }

        else if ((i >= 10) && (i < 11))	// 主菜单左侧菜单
        {
            obj_menu_item = lv_img_create(lv_tabview_get_tab(tabview_desktop, 0), NULL);
            label_app_name = lv_label_create(lv_tabview_get_tab(tabview_desktop, 0), NULL);
        }
        else							// 主菜单右侧菜单
        {
            obj_menu_item = lv_img_create(lv_tabview_get_tab(tabview_desktop, 2), NULL);
            label_app_name = lv_label_create(lv_tabview_get_tab(tabview_desktop, 2), NULL);
        }
		
        lv_obj_set_click(obj_menu_item, 1);            // 允许点击
        lv_img_set_src(obj_menu_item, app_icon[i]);    // 使用数组文件
        lv_obj_set_drag(obj_menu_item, true);        // 启用拖动
        lv_obj_align(obj_menu_item, NULL, LV_ALIGN_IN_TOP_LEFT, col_space, row_space);
        lv_obj_fade_in(obj_menu_item, 0 , delay);
        lv_obj_set_event_cb(obj_menu_item, lv_100ask_event_cb[i]);    /* 分配事件回调处理函数 */
		
		/* 创建 app name 标签 */
        lv_obj_set_style_local_text_font(label_app_name, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_14);  	// 设置字号
        lv_label_set_text(label_app_name, app_name[i]);
        lv_obj_align(label_app_name, obj_menu_item, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
        lv_obj_fade_in(label_app_name, 0 , delay);


        col_count++;

        if (((i + 1) % 4) == 0)  // 换行，一行最多有4个图标
        {
            col_count = 0;
            row_count++;
            row_space = ((((LV_100ASK_BOTTOM_MENU_W - (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * LV_100ASK_BOTTOM_MENU_ITEM_COUNT)) / 5) * (row_count + 1)) + (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * row_count));
        }
        col_space = ((((LV_100ASK_BOTTOM_MENU_W - (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * LV_100ASK_BOTTOM_MENU_ITEM_COUNT)) / 5) * (col_count + 1)) + (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * col_count));
    }


    /* 创建底部导航栏展示区域 */
    lv_obj_t * obj_bottom_menu = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(obj_bottom_menu, LV_100ASK_BOTTOM_MENU_W, LV_100ASK_BOTTOM_MENU_H);                                  // 设置大小
    lv_obj_set_style_local_bg_opa(obj_bottom_menu, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_50);                       // 设置背景透明度
    lv_obj_set_style_local_radius(obj_bottom_menu, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);                               // 设置圆角
    lv_obj_set_style_local_bg_color(obj_bottom_menu, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_100ASK_BOTTOM_MENU_COLOR);   // 设置颜色
	lv_obj_set_style_local_border_width(obj_bottom_menu, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_align(obj_bottom_menu, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_fade_in(obj_bottom_menu, 0 , delay);

    /* 创建底部导航栏内的菜单 */
    lv_obj_t * obj_bottom_menu_item;
    for (int i = 0; i < LV_100ASK_BOTTOM_MENU_ITEM_COUNT; i++)
    {
        obj_bottom_menu_item = lv_img_create(obj_bottom_menu, NULL);
        lv_obj_set_click(obj_bottom_menu_item, 1);            // 允许点击
        lv_img_set_src(obj_bottom_menu_item, app_icon[i]);    // 使用数组文件
        lv_obj_set_drag(obj_bottom_menu_item, true);        // 启用拖动
        lv_obj_align(obj_bottom_menu_item, NULL, LV_ALIGN_IN_LEFT_MID, ((((LV_100ASK_BOTTOM_MENU_W - (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * LV_100ASK_BOTTOM_MENU_ITEM_COUNT)) / 5) * (i + 1))\
                                                                     + (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * i)), 0);
        lv_obj_fade_in(obj_bottom_menu_item, 0 , delay);
        lv_obj_set_event_cb(obj_bottom_menu_item, lv_100ask_event_cb[i]);    /* 分配事件回调处理函数 */
    }
}

/**********************************************************************
 * 功能描述： 打开关于应用
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_setting(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED)
    {
        lv_setting();
		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
		msh_exec("free", rt_strlen("free"));
        lv_obj_del(tabview_desktop);
        msh_exec("free", rt_strlen("free"));
    }
}


// /**********************************************************************
//  * 函数名称： event_handler_stm32_demo_music_player
//  * 功能描述： 打开音乐播放器应用
//  * 输入参数： 触发事件的对象(图标)
//  * 输入参数： 事件触发的事件类型
//  * 输出参数： 无
//  * 返 回 值： 无
//  * 修改日期              版本号      修改人	      修改内容
//  * ---------------------------------------------------------------------
//  * 2020/11/11	     V1.0	  YobeZhou    创建
//  ***********************************************************************/
// static void event_handler_stm32_demo_music_player(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
// 		lv_obj_del(tabview_desktop);
// 		lv_100ask_stm32_music_player();
//     }
// }



// /**********************************************************************
//  * 函数名称： event_handler_stm32_demo_game_2048
//  * 功能描述： 打开2048游戏
//  * 输入参数： 触发事件的对象(图标)
//  * 输入参数： 事件触发的事件类型
//  * 输出参数： 无
//  * 返 回 值： 无
//  * 修改日期              版本号      修改人	      修改内容
//  * ---------------------------------------------------------------------
//  * 2020/11/11	     V1.0	  YobeZhou    创建
//  ***********************************************************************/
// static void event_handler_stm32_demo_game_2048(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
// 		lv_obj_del(tabview_desktop);
//         lv_100ask_game_2048();
//     }
// }


// /**********************************************************************
//  * 函数名称： event_handler_stm32_demo_tools_regbit
//  * 功能描述： 打开寄存器位查看计算工具
//  * 输入参数： 触发事件的对象(图标)
//  * 输入参数： 事件触发的事件类型
//  * 输出参数： 无
//  * 返 回 值： 无
//  * 修改日期              版本号      修改人	      修改内容
//  * ---------------------------------------------------------------------
//  * 2020/11/11	     V1.0	  YobeZhou    创建
//  ***********************************************************************/
// static void event_handler_stm32_demo_tools_regbit(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
// 		lv_obj_del(tabview_desktop);
//         lv_100ask_stm32_tool_regbit();
//     }
// }

 
// /**********************************************************************
//  * 函数名称： event_handler_stm32_demo_tools_qrcode
//  * 功能描述： 打开二维码创建工具
//  * 输入参数： 触发事件的对象(图标)
//  * 输入参数： 事件触发的事件类型
//  * 输出参数： 无
//  * 返 回 值： 无
//  * 修改日期              版本号      修改人	      修改内容
//  * ---------------------------------------------------------------------
//  * 2020/11/11	     V1.0	  YobeZhou    创建
//  ***********************************************************************/
// static void event_handler_stm32_demo_tools_qrcode(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
//         lv_obj_del(tabview_desktop);
//         lv_100ask_stm32_tool_qrcode();
//     }
// }

// /**********************************************************************
//  * 函数名称： event_handler_stm32_demo_tools_calc
//  * 功能描述： 打开计算器
//  * 输入参数： 触发事件的对象(图标)
//  * 输入参数： 事件触发的事件类型
//  * 输出参数： 无
//  * 返 回 值： 无
//  * 修改日期              版本号      修改人	      修改内容
//  * ---------------------------------------------------------------------
//  * 2020/11/11	     V1.0	  YobeZhou    创建
//  ***********************************************************************/
// static void event_handler_stm32_demo_tools_calc(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
//         lv_obj_del(tabview_desktop);
//         lv_100ask_stm32_tool_calc();
//     }
// }


// /**********************************************************************
//  * 函数名称： event_handler_stm32_demo_tools_file_browser
//  * 功能描述： 打开文件浏览器
//  * 输入参数： 触发事件的对象(图标)
//  * 输入参数： 事件触发的事件类型
//  * 输出参数： 无
//  * 返 回 值： 无
//  * 修改日期              版本号      修改人	      修改内容
//  * ---------------------------------------------------------------------
//  * 2020/11/11	     V1.0	  YobeZhou    创建
//  ***********************************************************************/
// static void event_handler_stm32_demo_tools_file_browser(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
//         lv_obj_del(tabview_desktop);
//         lv_100ask_stm32_tool_file_browser();
//     }
// }



// /**********************************************************************
//  * 函数名称： event_handler_stm32_demo_tools_snake
//  * 功能描述： 打开贪吃蛇游戏
//  * 输入参数： 触发事件的对象(图标)
//  * 输入参数： 事件触发的事件类型
//  * 输出参数： 无
//  * 返 回 值： 无
//  * 修改日期              版本号      修改人	      修改内容
//  * ---------------------------------------------------------------------
//  * 2020/11/11	     V1.0	  YobeZhou    创建
//  ***********************************************************************/
// static void event_handler_stm32_demo_game_snake(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
//         lv_obj_del(tabview_desktop);
//         lv_100ask_stm32_game_snake();
//     }
// }


// /**********************************************************************
//  * 函数名称： event_handler_stm32_demo_tools_clock
//  * 功能描述： 打开时钟
//  * 输入参数： 触发事件的对象(图标)
//  * 输入参数： 事件触发的事件类型
//  * 输出参数： 无
//  * 返 回 值： 无
//  * 修改日期              版本号      修改人	      修改内容
//  * ---------------------------------------------------------------------
//  * 2020/11/11	     V1.0	  YobeZhou    创建
//  ***********************************************************************/
// static void event_handler_stm32_demo_tools_clock(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
//         lv_obj_del(tabview_desktop);
//         lv_100ask_stm32_tool_clock();
//     }
// }


// /**********************************************************************
//  * 函数名称： event_handler_stm32_demo_tools_humiture
//  * 功能描述： 打开温湿度检测应用
//  * 输入参数： 触发事件的对象(图标)
//  * 输入参数： 事件触发的事件类型
//  * 输出参数： 无
//  * 返 回 值： 无
//  * 修改日期              版本号      修改人	      修改内容
//  * ---------------------------------------------------------------------
//  * 2020/11/11	     V1.0	  YobeZhou    创建
//  ***********************************************************************/
// static void event_handler_stm32_demo_tools_humiture(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
//         lv_obj_del(tabview_desktop);
//         lv_100ask_stm32_tool_humiture();
//     }
// }


// /**********************************************************************
//  * 函数名称： event_handler_stm32_demo_tools_widget_test
//  * 功能描述： 打开板载部件测试应用
//  * 输入参数： 触发事件的对象(图标)
//  * 输入参数： 事件触发的事件类型
//  * 输出参数： 无
//  * 返 回 值： 无
//  * 修改日期              版本号      修改人	      修改内容
//  * ---------------------------------------------------------------------
//  * 2020/11/11	     V1.0	  YobeZhou    创建
//  ***********************************************************************/
// static void event_handler_stm32_demo_tools_widget_test(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
//         lv_obj_del(tabview_desktop);
//         lv_100ask_stm32_tool_widget_test();
//     }
// }


// /**********************************************************************
//  * 函数名称： event_handler_stm32_demo_tools_settings
//  * 功能描述： 打开系统设置
//  * 输入参数： 触发事件的对象(图标)
//  * 输入参数： 事件触发的事件类型
//  * 输出参数： 无
//  * 返 回 值： 无
//  * 修改日期              版本号      修改人	      修改内容
//  * ---------------------------------------------------------------------
//  * 2020/11/11	     V1.0	  YobeZhou    创建
//  ***********************************************************************/
// static void event_handler_stm32_demo_tools_settings(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		tabview_desktop_id = lv_tabview_get_tab_act(tabview_desktop); 	// 记录当前页面位置
//         lv_obj_del(tabview_desktop);
//         lv_100ask_stm32_tool_setting();
//     }
// }
