#include "motor.h"

#define SAMPLE_UART_NAME                 "uart2"
#define DATA_CMD_END                     '\r'       /* 结束位设置为 \r，即回车符 */
#define ONE_DATA_MAXLEN                  10         /* 不定长数据的最大长度 */

/* 用于接收消息的信号量 */
static struct rt_semaphore motor_rx_sem;
struct rt_serial_device *motor_serial;

/* 接收数据回调函数 */
static rt_err_t uart_rx_ind(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    if (size > 0)
    {
        rt_sem_release(&motor_rx_sem);
    }
    return RT_EOK;
}

static char uart_sample_get_char(void)
{
    char ch;

    while (rt_device_read(motor_serial, 0, &ch, 1) == 0)
    {
        rt_sem_control(&motor_rx_sem, RT_IPC_CMD_RESET, RT_NULL);
        rt_sem_take(&motor_rx_sem, RT_WAITING_FOREVER);
    }
    return ch;
}

/* 数据解析线程 */
static void data_parsing(void)
{
    char ch;
    char data[ONE_DATA_MAXLEN];
    static char i = 0;

    while (1)
    {
        ch = uart_sample_get_char();
        if(ch == DATA_CMD_END)
        {
            if(0 == rt_strncmp(data, "init", 4))
            {
                rt_kprintf("motor initialization succeeded!\r\n");
            }
            else if(0 == rt_strncmp(data, "done", 4))
            {

            }
            i = 0;
            continue;
        }
        i = (i >= ONE_DATA_MAXLEN-1) ? ONE_DATA_MAXLEN-1 : i;
        data[i++] = ch;
    }
}

static rt_err_t rt_motor_init(struct rt_device *device)
{
    rt_motor_t motor = (rt_motor_t)device;
    motor_serial = motor->serial_device;

    rt_err_t ret = RT_EOK;
    char str[] = "90,10,180,10,210,10\r";

    rt_sem_init(&motor_rx_sem, "motor_rx_sem", 0, RT_IPC_FLAG_PRIO);
    rt_device_open(motor_serial, RT_DEVICE_FLAG_INT_RX);
    rt_device_set_rx_indicate(motor_serial, uart_rx_ind);
    rt_device_write(motor_serial, 0, str, (sizeof(str) - 1));
    
    rt_thread_t thread = rt_thread_create("motor_serial", data_parsing, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;

}

static rt_err_t rt_motor_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    rt_motor_t motor = (rt_motor_t)dev;

    switch (cmd)
    {
        case RT_MOTOR_CTRL_SET_SPEED:
            char *str = (char *)args;
            rt_device_write(motor_serial, 0, str, (sizeof(str) - 1));
        break;
        
        case RT_TOUCH_CTRL_GET_INFO:
        default:
            struct rt_motor_info *motor_info = (struct rt_motor_info *)args;
            motor_info->type   = motor->info.type;
            motor_info->vendor = motor->info.vendor;
        break;
    }

    return result;
}

int rt_hw_motor_register(rt_motor_t  motor,
                         const char  *name,
                         rt_uint32_t flag,
                         void        *data)
{
    rt_int8_t result;
    rt_device_t device;

    device = &motor->parent;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &rt_motor_ops;
#else
    device->init        = rt_motor_init;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = rt_motor_control;
#endif
    device->type        = RT_Device_Class_Unknown;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->user_data   = data;

    result = rt_device_register(device, name, flag | RT_DEVICE_FLAG_STANDALONE);

    if (result != RT_EOK)
    {
        LOG_E("rt_motor register err code: %d", result);
        return result;
    }

    LOG_I("rt_motor init success");

    return RT_EOK;
}
