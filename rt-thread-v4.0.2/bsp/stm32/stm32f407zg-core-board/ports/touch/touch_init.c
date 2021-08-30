#include "board.h"
#include "touch.h"
#include "gt917s.h"

#if defined(PKG_USING_GT917S)

#define GT917S_RST_PIN    GET_PIN(C, 13)
#define GT917S_IRQ_PIN    GET_PIN(B, 1)

int rt_hw_gt917s_port(void)
{
    struct rt_touch_config config;
    rt_uint8_t rst;
    
    rst = GT917S_RST_PIN;
    config.dev_name = "i2c1";
    config.irq_pin.pin  = GT917S_IRQ_PIN;
    config.irq_pin.mode = PIN_MODE_INPUT_PULLUP;
    config.user_data = &rst;
	
    rt_hw_gt917s_init("gt917s", &config);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_gt917s_port);
#endif
