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
#define RT_USING_SMALL_MEM
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart0"
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
//#define FINSH_USING_MSH_ONLY
#define FINSH_ARG_MAX 10

/* Device virtual file system */

//#define RT_USING_DFS
//#define DFS_USING_WORKDIR
//#define DFS_FILESYSTEMS_MAX 2
//#define DFS_FILESYSTEM_TYPES_MAX 2
//#define DFS_FD_MAX 16
//#define RT_USING_DFS_MNTTABLE
//#define RT_USING_DFS_ELMFAT

/* elm-chan's FatFs, Generic FAT Filesystem Module */

//#define RT_DFS_ELM_CODE_PAGE 437
//#define RT_DFS_ELM_WORD_ACCESS
//#define RT_DFS_ELM_USE_LFN_3
//#define RT_DFS_ELM_USE_LFN 3
//#define RT_DFS_ELM_MAX_LFN 255
//#define RT_DFS_ELM_DRIVES 2
//#define RT_DFS_ELM_MAX_SECTOR_SIZE 4096
//#define RT_DFS_ELM_REENTRANT
//#define RT_USING_DFS_DEVFS

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_PIPE_BUFSZ 512
#define RT_USING_SYSTEM_WORKQUEUE
#define RT_SYSTEM_WORKQUEUE_STACKSIZE 2048
#define RT_SYSTEM_WORKQUEUE_PRIORITY 23
#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
#define RT_SERIAL_RB_BUFSZ 64
#define RT_USING_PIN
//#define RT_USING_RTC
//#define RT_USING_SPI
//#define RT_USING_SFUD
//#define RT_SFUD_USING_SFDP
//#define RT_SFUD_USING_FLASH_INFO_TABLE
//#define RT_SFUD_SPI_MAX_HZ 50000000
//#define RT_USING_ENC28J60

/* Using USB */


/* POSIX layer and C standard library */

//#define RT_USING_LIBC
//#define RT_USING_POSIX

/* Network */

/* Socket abstraction layer */

//#define RT_USING_SAL

/* protocol stack implement */

//#define SAL_USING_POSIX

/* Network interface device */

//#define RT_USING_NETDEV
//#define NETDEV_USING_IFCONFIG
//#define NETDEV_USING_PING
//#define NETDEV_USING_NETSTAT
//#define NETDEV_USING_AUTO_DEFAULT
//#define NETDEV_IPV4 1
//#define NETDEV_IPV6 0

/* light weight TCP/IP stack */

//#define RT_USING_LWIP
//#define RT_USING_LWIP202
//#define RT_LWIP_IGMP
//#define RT_LWIP_ICMP
//#define RT_LWIP_DNS
//#define RT_LWIP_DHCP
//#define IP_SOF_BROADCAST 1
//#define IP_SOF_BROADCAST_RECV 1

/* Static IPv4 Address */

//#define RT_LWIP_IPADDR "192.168.0.212"
//#define RT_LWIP_GWADDR "192.168.0.1"
//#define RT_LWIP_MSKADDR "255.255.255.0"
//#define RT_LWIP_UDP
//#define RT_LWIP_TCP
//#define RT_LWIP_RAW
//#define RT_MEMP_NUM_NETCONN 8
//#define RT_LWIP_PBUF_NUM 16
//#define RT_LWIP_RAW_PCB_NUM 4
//#define RT_LWIP_UDP_PCB_NUM 4
//#define RT_LWIP_TCP_PCB_NUM 4
//#define RT_LWIP_TCP_SEG_NUM 40
//#define RT_LWIP_TCP_SND_BUF 8196
//#define RT_LWIP_TCP_WND 8196
//#define RT_LWIP_TCPTHREAD_PRIORITY 10
//#define RT_LWIP_TCPTHREAD_MBOX_SIZE 8
//#define RT_LWIP_TCPTHREAD_STACKSIZE 1024
//#define RT_LWIP_ETHTHREAD_PRIORITY 12
//#define RT_LWIP_ETHTHREAD_STACKSIZE 1024
//#define RT_LWIP_ETHTHREAD_MBOX_SIZE 8
//#define LWIP_NETIF_STATUS_CALLBACK 1
//#define LWIP_NETIF_LINK_CALLBACK 1
//#define SO_REUSE 1
//#define LWIP_SO_RCVTIMEO 1
//#define LWIP_SO_SNDTIMEO 1
//#define LWIP_SO_RCVBUF 1
//#define LWIP_NETIF_LOOPBACK 0
//#define RT_LWIP_USING_PING

/* AT commands */

//#define LWIP_USING_DHCPD
//#define DHCPD_SERVER_IP "192.168.0.1"
//#define DHCPD_USING_ROUTER
//#define LWIP_USING_CUSTOMER_DNS_SERVER
//#define DHCP_DNS_SERVER_IP "192.168.0.1"

/* VBUS(Virtual Software BUS) */


/* Utilities */


/* RT-Thread online packages */

/* IoT - internet of things */

//#define PKG_USING_WEBCLIENT
//#define WEBCLIENT_DEBUG
//#define WEBCLIENT_USING_SAMPLES
//#define WEBCLIENT_USING_FILE_DOWMLOAD
//#define WEBCLIENT_USING_MBED_TLS
//#define PKG_USING_WEBCLIENT_V212
//#define PKG_WEBCLIENT_VER_NUM 0x20102
//#define PKG_USING_CJSON
//#define PKG_USING_CJSON_LATEST_VERSION

/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */

//#define PKG_USING_NETUTILS
//#define PKG_NETUTILS_IPERF
//#define PKG_NETUTILS_NETIO
//#define PKG_USING_NETUTILS_V120

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


/* tools packages */


/* system packages */

//#define PKG_USING_FAL
//#define FAL_DEBUG_CONFIG
//#define FAL_DEBUG 1
//#define FAL_PART_HAS_TABLE_CFG
//#define FAL_USING_SFUD_PORT
//#define FAL_USING_NOR_FLASH_DEV_NAME "W25Q128"
//#define PKG_USING_FAL_V00500
//#define PKG_FAL_VER_NUM 0x00500

/* peripheral libraries and drivers */


/* miscellaneous packages */


/* samples: kernel and components samples */

//#define PKG_USING_NETWORK_SAMPLES
//#define PKG_USING_NETWORK_SAMPLES_V030
//#define NETWORK_SAMPLES_USING_TCP_CLIENT
//#define NETWORK_SAMPLES_USING_TCP_SERVER
//#define NETWORK_SAMPLES_USING_UDP_CLIENT
//#define NETWORK_SAMPLES_USING_UDP_SERVER
//#define NETWORK_SAMPLES_USING_TCP_CLIENT_SELECT
//#define NETWORK_SAMPLES_USING_HTTP_CLIENT
//#define SOC_FAMILY_STM32
//#define SOC_SERIES_STM32F4

/* entertainment: terminal games and other interesting software packages */

#define SOC_GD32450Z
#define BSP_USING_GPIO
#define BSP_USING_UART
#define BSP_USING_UART0
//#define BSP_USING_ON_CHIP_FLASH
//#define BSP_USING_SPI
//#define BSP_USING_SPI1
//#define BSP_USING_SPI2

/* Hardware Drivers Config */

/* Onboard Peripheral Drivers */

#define BSP_USING_USB_TO_USART
//#define BSP_USING_SPI_FLASH

/* On-chip Peripheral Drivers */

/* Board extended module Drivers */


#endif
