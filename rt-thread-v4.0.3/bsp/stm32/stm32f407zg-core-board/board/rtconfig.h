#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 1024

/* kservice optimization */

#define RT_DEBUG
#define RT_DEBUG_COLOR

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_MEMHEAP
#define RT_USING_MEMHEAP_AS_HEAP
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart1"
#define RT_VER_NUM 0x40003
#define ARCH_ARM
#define RT_USING_CPU_FFS
#define ARCH_ARM_CORTEX_M
#define ARCH_ARM_CORTEX_M4

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 2048
#define RT_MAIN_THREAD_PRIORITY 10

/* C++ features */


/* Command shell */

#define RT_USING_FINSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_CMD_SIZE 80
#define FINSH_USING_MSH
#define FINSH_USING_MSH_DEFAULT
#define FINSH_USING_MSH_ONLY
#define FINSH_ARG_MAX 10

/* Device virtual file system */

#define RT_USING_DFS
#define DFS_USING_WORKDIR
#define DFS_FILESYSTEMS_MAX 3
#define DFS_FILESYSTEM_TYPES_MAX 2
#define DFS_FD_MAX 16
//#define RT_USING_DFS_MNTTABLE
#define RT_USING_DFS_ELMFAT

/* elm-chan's FatFs, Generic FAT Filesystem Module */

#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_USE_LFN_3
#define RT_DFS_ELM_USE_LFN 3
#define RT_DFS_ELM_LFN_UNICODE_0
#define RT_DFS_ELM_LFN_UNICODE 0
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 2
#define RT_DFS_ELM_MAX_SECTOR_SIZE 4096
#define RT_DFS_ELM_REENTRANT
#define RT_USING_DFS_DEVFS

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_PIPE_BUFSZ 512
#define RT_USING_SYSTEM_WORKQUEUE
#define RT_SYSTEM_WORKQUEUE_STACKSIZE 2048
#define RT_SYSTEM_WORKQUEUE_PRIORITY 23
#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
#define RT_SERIAL_RB_BUFSZ 64
#define RT_USING_I2C
#define RT_USING_I2C_BITOPS
#define RT_USING_PIN
#define RT_USING_SDIO
#define RT_SDIO_STACK_SIZE 512
#define RT_SDIO_THREAD_PRIORITY 15
#define RT_MMCSD_STACK_SIZE 1024
#define RT_MMCSD_THREAD_PREORITY 22
#define RT_MMCSD_MAX_PARTITION 16
#define RT_USING_TOUCH
#define RT_TOUCH_PIN_IRQ
//#define RT_USING_RTC
#define RT_USING_SPI
#define RT_USING_SFUD
#define RT_SFUD_USING_SFDP
#define RT_SFUD_USING_FLASH_INFO_TABLE
#define RT_SFUD_SPI_MAX_HZ 50000000
#define RT_USING_ENC28J60

/* Using USB */


/* POSIX layer and C standard library */

#define RT_USING_LIBC
#define RT_USING_POSIX
#define RT_USING_POSIX_TERMIOS

/* Network */

/* Socket abstraction layer */

#define RT_USING_SAL
#define SAL_INTERNET_CHECK

/* protocol stack implement */

#define SAL_USING_POSIX
#define SAL_USING_AT
#define SAL_SOCKETS_NUM 16

/* Network interface device */

#define RT_USING_NETDEV
#define NETDEV_USING_IFCONFIG
#define NETDEV_USING_PING
#define NETDEV_USING_NETSTAT
#define NETDEV_USING_AUTO_DEFAULT
#define NETDEV_IPV4 1
#define NETDEV_IPV6 0

/* light weight TCP/IP stack */

#define RT_USING_LWIP
#define RT_USING_LWIP202
#define RT_LWIP_IGMP
#define RT_LWIP_ICMP
#define RT_LWIP_DNS
//#define RT_LWIP_DHCP
#define IP_SOF_BROADCAST 1
#define IP_SOF_BROADCAST_RECV 1

/* Static IPv4 Address */

#define RT_LWIP_IPADDR "192.168.0.212"
#define RT_LWIP_GWADDR "192.168.0.1"
#define RT_LWIP_MSKADDR "255.255.255.0"
#define RT_LWIP_UDP
#define RT_LWIP_TCP
#define RT_LWIP_RAW
#define RT_MEMP_NUM_NETCONN 8
#define RT_LWIP_PBUF_NUM 16
#define RT_LWIP_RAW_PCB_NUM 4
#define RT_LWIP_UDP_PCB_NUM 4
#define RT_LWIP_TCP_PCB_NUM 4
#define RT_LWIP_TCP_SEG_NUM 40
#define RT_LWIP_TCP_SND_BUF 8196
#define RT_LWIP_TCP_WND 8196
#define RT_LWIP_TCPTHREAD_PRIORITY 10
#define RT_LWIP_TCPTHREAD_MBOX_SIZE 8
#define RT_LWIP_TCPTHREAD_STACKSIZE 1024
#define RT_LWIP_ETHTHREAD_PRIORITY 12
#define RT_LWIP_ETHTHREAD_STACKSIZE 1024
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 8
#define LWIP_NETIF_STATUS_CALLBACK 1
#define LWIP_NETIF_LINK_CALLBACK 1
#define SO_REUSE 1
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1
#define LWIP_SO_RCVBUF 1
#define LWIP_NETIF_LOOPBACK 0
#define RT_LWIP_USING_PING

/* AT commands */

#define LWIP_USING_DHCPD
#define DHCPD_SERVER_IP "192.168.0.1"
#define DHCPD_USING_ROUTER
#define LWIP_USING_CUSTOMER_DNS_SERVER
#define DHCP_DNS_SERVER_IP "192.168.0.1"

#define RT_USING_AT
#define AT_USING_CLIENT
#define AT_CLIENT_NUM_MAX 1
#define AT_USING_SOCKET
#define AT_USING_CLI
#define AT_CMD_MAX_LEN 128
#define AT_SW_VERSION_NUM 0x10301

/* VBUS(Virtual Software BUS) */


/* Utilities */


/* RT-Thread online packages */

/* IoT - internet of things */

#define PKG_USING_WEBCLIENT
#define WEBCLIENT_DEBUG
#define WEBCLIENT_USING_SAMPLES
#define WEBCLIENT_USING_FILE_DOWMLOAD
//#define WEBCLIENT_USING_MBED_TLS
#define PKG_USING_WEBCLIENT_V212
#define PKG_WEBCLIENT_VER_NUM 0x20102
#define PKG_USING_CJSON
#define PKG_USING_CJSON_LATEST_VERSION

/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */

#define PKG_USING_NETUTILS
#define PKG_NETUTILS_IPERF
#define PKG_NETUTILS_NETIO
#define PKG_USING_NETUTILS_V120

#define PKG_USING_AT_DEVICE
#define AT_DEVICE_USING_ESP8266
#define AT_DEVICE_ESP8266_INIT_ASYN
#define AT_DEVICE_ESP8266_SAMPLE
#define ESP8266_SAMPLE_WIFI_SSID "rtthread"
#define ESP8266_SAMPLE_WIFI_PASSWORD "12345678"
#define ESP8266_SAMPLE_CLIENT_NAME "uart2"
#define ESP8266_SAMPLE_RECV_BUFF_LEN 512
#define PKG_USING_AT_DEVICE_V204
#define PKG_AT_DEVICE_VER_NUM 0x20004

/* IoT Cloud */


/* security packages */

//#define PKG_USING_MBEDTLS

/* Select Root Certificate */

//#define PKG_USING_MBEDTLS_DIGICERT_ROOT_CA
//#define PKG_USING_MBEDTLS_DST_ROOT_CA
//#define MBEDTLS_AES_ROM_TABLES
//#define MBEDTLS_ECP_WINDOW_SIZE 2
//#define MBEDTLS_SSL_MAX_CONTENT_LEN 3584
//#define PKG_USING_MBEDTLS_EXAMPLE
//#define PKG_USING_MBEDTLS_DEBUG
//#define PKG_USING_MBEDTLS_LATEST_VERSION

/* language packages */


/* multimedia packages */

//#define PKG_USING_STEMWIN
//#define PKG_STEMWIN_MEM_SIZE 60
//#define PKG_USING_STEMWIN_EXAMPLE
//#define PKG_USING_STEMWIN_LATEST_VERSION
//#define PKG_STEMWIN_VER_NUM 0x99999

#define PKG_USING_TJPGD
#define TJPGD_INPUT_BUFFER_SIZE 3072
#define TJPGD_USING_FORMAT_RGB565
#define TJPGD_USING_SCALE
#define TJPGD_USING_TBLCLIP
#define PKG_TJPGD_SAMPLE
#define PKG_USING_TJPGD_LATEST_VERSION

/* tools packages */

#define PKG_USING_MEM_SANDBOX
#define PKG_USING_MEM_SANDBOX_LATEST_VERSION

/* system packages */

#define PKG_USING_FAL
#define FAL_DEBUG_CONFIG
#define FAL_DEBUG 1
#define FAL_PART_HAS_TABLE_CFG
#define FAL_USING_SFUD_PORT
#define FAL_USING_NOR_FLASH_DEV_NAME "W25Q128"
#define PKG_USING_FAL_V00500
#define PKG_FAL_VER_NUM 0x00500

#define PKG_USING_LITTLEVGL2RTT
#define PKG_USING_LITTLEVGL2RTT_LATEST_VERSION

/* LittlevGL2RTT Options */

#define LV_MEM_DYNAMIC
#define LV_MEM_CUSTOM 1
#define LV_COLOR_DEPTH_16
#define LV_COLOR_DEPTH 16
#define LV_HOR_RES 800
#define LV_VER_RES 480
#define LV_DPI 217
#define LV_PNG_USE_LV_FILESYSTEM 1
#define LITTLEVGL2RTT_USING_DEMO
#define LV_EX_CONF_INCLUDE_SIMPLE

/* peripheral libraries and drivers */

#define SDIO_MAX_FREQ 1000000
#define PKG_USING_I2C_TOOLS
#define I2C_TOOLS_USE_SW_I2C
#define I2C_TOOLS_SW_ACK_TIMEOUT 100
#define PKG_USING_I2C_TOOLS_LATEST_VERSION
#define PKG_USING_TOUCH_DRIVERS
#define PKG_USING_GT917S
#define PKG_USING_GT917S_LATEST_VERSION

/* miscellaneous packages */

/* samples: kernel and components samples */

#define PKG_USING_NETWORK_SAMPLES
#define PKG_USING_NETWORK_SAMPLES_V030
#define NETWORK_SAMPLES_USING_TCP_CLIENT
#define NETWORK_SAMPLES_USING_TCP_SERVER
#define NETWORK_SAMPLES_USING_UDP_CLIENT
#define NETWORK_SAMPLES_USING_UDP_SERVER
#define NETWORK_SAMPLES_USING_TCP_CLIENT_SELECT
#define NETWORK_SAMPLES_USING_HTTP_CLIENT

#define PKG_USING_VT100
#define VT100_USING_MONITOR
#define VT100_USING_COLOR
#define VT100_USING_SL
#define VT100_USING_IMGBUF
#define VT100_USING_LSIMG
#define PKG_USING_VT100_LATEST_VERSION
#define PKG_VT100_VER_NUM 0x99999

/* entertainment: terminal games and other interesting software packages */

#define PKG_USING_2048
#define PKG_USING_2048_LATEST_VERSION

#define PKG_USING_OPTPARSE
#define PKG_USING_OPTPARSE_LATEST_VERSION

#define PKG_USING_VI
#define VI_SANDBOX_SIZE_KB 40
#define VI_MAX_LEN 4096
#define VI_ENABLE_8BIT
#define VI_ENABLE_COLON
#define VI_ENABLE_COLON_EXPAND
#define VI_ENABLE_YANKMARK
#define VI_ENABLE_SEARCH
#define VI_ENABLE_DOT_CMD
#define VI_ENABLE_READONLY
#define VI_ENABLE_SETOPTS
#define VI_ENABLE_SET
#define VI_ENABLE_WIN_RESIZE
#define VI_ENABLE_VI_ASK_TERMINAL
#define VI_ENABLE_UNDO
#define VI_ENABLE_UNDO_QUEUE
#define VI_UNDO_QUEUE_MAX 256
#define VI_ENABLE_VERBOSE_STATUS
#define PKG_USING_VI_LATEST_VERSION

#define SOC_FAMILY_STM32
#define SOC_SERIES_STM32F4

/* Hardware Drivers Config */

#define SOC_STM32F407ZG

/* Onboard Peripheral Drivers */

#define BSP_USING_USB_TO_USART
#define BSP_USING_SPI_FLASH
#define BSP_USING_SDCARD
#define BSP_USING_SRAM

/* On-chip Peripheral Drivers */

#define BSP_USING_GPIO
#define BSP_USING_UART
#define BSP_USING_UART1
#define BSP_USING_UART2
#define BSP_USING_I2C1
#define BSP_I2C1_SCL_PIN GET_PIN(B, 0)
#define BSP_I2C1_SDA_PIN GET_PIN(F, 11)
#define BSP_USING_EXT_FMC_IO
#define BSP_USING_FMC
#define BSP_USING_ON_CHIP_FLASH
#define BSP_USING_SPI
#define BSP_USING_SPI1
#define BSP_USING_SPI2
#define BSP_USING_SDIO

/* Board extended module Drivers */


#endif
