#ifndef __LCD_PORT_H
#define __LCD_PORT_H

#define LCD_RES_GPIO_NUM   GET_PIN(B, 7)

#define LCD_CS_GPIO_NUM    GET_PIN(G, 10)
#define LCD_SCLK_GPIO_NUM  GET_PIN(B, 13)
#define LCD_MOSI_GPIO_NUM  GET_PIN(B, 15)

#define LCD_WIDTH          480 //LCD水平分辨率
#define LCD_HEIGHT         320 //LCD垂直分辨率

#define LCD_HSYNC_WIDTH    4   //水平脉宽
#define LCD_HBP            100 //水平后廊
#define LCD_HFP            20  //水平前廊

#define LCD_VSYNC_HEIGHT   4   //垂直脉宽
#define LCD_VBP            200 //垂直后廊
#define LCD_VFP            20  //垂直前廊

#define LCD_BITS_PER_PIXEL 16                                                //像素位数
#define LCD_PIXEL_FORMAT   RTGRAPHIC_PIXEL_FORMAT_RGB565                     //像素格式
#define LCD_BUF_SIZE       LCD_WIDTH * LCD_HEIGHT * (LCD_BITS_PER_PIXEL / 8) //帧缓存大小

#endif
