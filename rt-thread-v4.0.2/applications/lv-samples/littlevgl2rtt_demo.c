#include "littlevgl2rtt.h" 
#include "lvgl.h" 

#include <rtthread.h> 
#include <rtdevice.h>  

//#include "lv_test_theme.h"
//#include "lv_examples.h"
//void lv_one_watch_main(void);
#include "lv_img_test.h"

//#include "gui_guider.h"
//#include "events_init.h"
//#include "custom.h"

//lv_ui guider_ui;

static void lvgl_demo_run(void *p)
{
//	lv_demo_widgets();
//	lv_one_watch_main();
//	lv_demo_printer();
	lv_demo_img_test();
	
	 /*Create a GUI-Guider app */
//	setup_ui(&guider_ui);
//    events_init(&guider_ui);
//    custom_init(&guider_ui);
}

int rt_lvgl_demo_init(void)
{
    rt_err_t ret = RT_EOK;
    rt_thread_t thread = RT_NULL;

    /* init littlevGL */ 
    ret = littlevgl2rtt_init("lcd"); 
    if(ret != RT_EOK)
    {
        return ret; 
    }

    /* littleGL demo gui thread */ 
    thread = rt_thread_create("lv_demo", lvgl_demo_run, RT_NULL, 10*1024, 5, 10); 
    if(thread == RT_NULL)
    {
        return RT_ERROR;
    }
    rt_thread_startup(thread);

    return RT_EOK; 
}
INIT_APP_EXPORT(rt_lvgl_demo_init); 
