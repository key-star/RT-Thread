#include "../lvgl/lvgl.h"

void lv_demo_img_test(void)
{
	lv_obj_t * img = lv_img_create(lv_scr_act(), NULL);
//	lv_img_set_src(img, "S:/example_16bit.bmp");
	lv_img_set_src(img, "S:/png_decoder_test.png");
//	lv_img_set_src(img, "S:/wallpaper.jpg");
//	lv_img_set_src(img, "S:/wallpaper.sjpg");
    lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, -20);
}
