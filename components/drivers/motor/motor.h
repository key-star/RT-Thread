#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <rtthread.h>
#include <rtdevice.h>

struct rt_motor_info
{
    rt_uint8_t     type;                       /* The motor type */
    rt_uint8_t     vendor;                     /* Vendor of motor */
};

struct rt_motor_device
{
    struct rt_device            parent;        /* The standard device */
    struct rt_motor_info        info;          /* The motor info data */

    /* serial device */
    struct rt_serial_device *serial_device;
};
typedef struct rt_motor_device *rt_motor_t;

#endif
