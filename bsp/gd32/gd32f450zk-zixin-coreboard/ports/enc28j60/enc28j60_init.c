/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-08-27     ZYLX              the first version
 */

#include <drivers/pin.h>
#include <enc28j60.h>
#include "drv_spi.h"
#include "board.h"

int enc28j60_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    rt_hw_spi_device_attach("spi2", "spi20", GPIOA, GPIO_PIN_1);

    /* attach enc28j60 to spi. spi20 cs - PA1 */
    enc28j60_attach("spi20");

    /* init interrupt pin */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
    rt_pin_mode(GET_PIN(C, 4), PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(GET_PIN(C, 4), PIN_IRQ_MODE_FALLING, (void(*)(void*))enc28j60_isr, RT_NULL);
    rt_pin_irq_enable(GET_PIN(C, 4), PIN_IRQ_ENABLE);

    return 0;
}
INIT_DEVICE_EXPORT(enc28j60_init);
