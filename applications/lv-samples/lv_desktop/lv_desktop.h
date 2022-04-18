/**
 * @file lv_desktop.h
 *
 */

#ifndef LV_DESKTOP_H
#define LV_DESKTOP_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
//#include "../../lv_100ask.h"
#include <rtthread.h>
#include "../lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define LV_100SK_STM32F103_DEMO_BG_BLACK           lv_color_hex(0xffffff)
#define LV_100SK_STM32F103_DEMO_BG_WHITE           lv_color_hex(0xffffff)
#define LV_100SK_STM32F103_DEMO_BG_LIGHT           lv_color_hex(0xf3f8fe)
#define LV_100SK_STM32F103_DEMO_BG_GRAY            lv_color_hex(0x8a8a8a)
#define LV_100SK_STM32F103_DEMO_BG_LIGHT_GRAY      lv_color_hex(0xc4c4c4)
#define LV_100SK_STM32F103_DEMO_BG_BLUE            lv_color_hex(0x2f3243) //006fb6
#define LV_100SK_STM32F103_DEMO_BG_GREEN           lv_color_hex(0x4cb242)
#define LV_100SK_STM32F103_DEMO_BG_RED             lv_color_hex(0xd51732)

/*Animations*/
#define LV_100SK_STM32F103_DEMO_ANIM_X 		       (LV_HOR_RES / 40)
#define LV_100SK_STM32F103_DEMO_ANIM_Y 		       (LV_VER_RES / 40)
#define LV_100SK_STM32F103_DEMO_ANIM_DELAY 	       (0)
#define LV_100SK_STM32F103_DEMO_ANIM_TIME  	       (0)

// SIZE
#define LV_100ASK_BOTTOM_MENU_W                    (LV_HOR_RES)
#define LV_100ASK_BOTTOM_MENU_H                    (76)
#define LV_100ASK_BOTTOM_MENU_ITEM_SIZE            (52)

// COLOR
#define LV_100ASK_BOTTOM_MENU_COLOR                (lv_color_hex(0xC9C9CE))
#define LV_100ASK_BOTTOM_MENU_ITEM_COUNT           (1)
#define LV_100ASK_MENU_ITEM_COUNT                  (1) 	//18 14

/*Padding*/
#define LV_100SK_STM32F103_DEMO_TITLE_PAD          (8)
#define LV_100SK_STM32F103_DEMO_BACK_W             (30)
#define LV_100SK_STM32F103_DEMO_BACK_H             (30)
#define LV_100SK_STM32F103_DEMO_BACK_PAD           (10)
#define LV_100ASK_TABVIEW_NAVIGATION_SPACE         (10)

// TIME
#define LV_100ASK_HOME_OPEN_TIME                   (0)


/**********************
 *      TYPEDEFS
 **********************/
 

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_desktop(uint32_t delay);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_DESKTOP_H */
