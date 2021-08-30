这是基于正点原子的STM32F407ZG核心开发板


GUI: LVGL 7.7.1

各组件基于官方库的修改

lv_lib_png-release-v7组件
1.lodepng.h文件第30行增加 #include "rtconfig.h"

lv_lib_bmp-master组件
1.lv_bmp.c文件第158行 LV_ASSERT_MALLOC 改为 LV_ASSERT_MEM
2.lv_bmp.c文件第183行去掉 , LV_FS_SEEK_SET