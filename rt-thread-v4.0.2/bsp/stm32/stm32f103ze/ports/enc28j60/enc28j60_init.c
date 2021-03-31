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
    rt_hw_spi_device_attach("spi1", "spi10", GPIOA, GPIO_PIN_4);

    /* attach enc28j60 to spi. spi10 cs - PA4 */
    enc28j60_attach("spi10");

    /* init interrupt pin */
	  __HAL_RCC_GPIOF_CLK_ENABLE();
    rt_pin_mode(GET_PIN(F, 0), PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(GET_PIN(F, 0), PIN_IRQ_MODE_FALLING, (void(*)(void*))enc28j60_isr, RT_NULL);
    rt_pin_irq_enable(GET_PIN(F, 0), PIN_IRQ_ENABLE);

    return 0;
}
INIT_COMPONENT_EXPORT(enc28j60_init);
