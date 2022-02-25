/*
 * File      : epidemic_sample.c
 *
 * Copyright (c) 2021-2021, key-star
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author      Notes
 * 2021-09-07     key-star     first version
 */

#include <webclient.h>  /* 使用 HTTP 协议与服务器通信需要包含此头文件 */
#include <sys/socket.h> /* 使用BSD socket，需要包含socket.h头文件 */
#include <netdb.h>
//#include <cJSON.h>
#include <finsh.h>
#include "dfs_posix.h"

#define GET_URL_LEN_MAX         256         //网址最大长度
#define GET_URI                 "https://view.inews.qq.com/g2/getOnsInfo?name=disease_h5"

void epidemic(int argc, char **argv)
{
	char *epidemic_url = RT_NULL;
	int result;
	
	/* 为 epidemic_url 分配空间 */
    epidemic_url = rt_calloc(1, GET_URL_LEN_MAX);
    if (epidemic_url == RT_NULL)
    {
        rt_kprintf("No memory for epidemic_url!\n");
        goto __exit;
    }
	rt_memset(epidemic_url, 0, GET_URL_LEN_MAX);
	
    /* 拼接 GET 网址 */
	rt_snprintf(epidemic_url, GET_URL_LEN_MAX, GET_URI);
	
	result = webclient_get_file(epidemic_url, "/sdcard/epidemic.json");
	if(result == 0)
	{
		rt_kprintf("webclient get file successfully\n");
	}
	else
	{
		rt_kprintf("GET request failed,the error code is %d\n", result);
	}
	
__exit:
    /* 释放网址空间 */
    if (epidemic_url != RT_NULL)
        rt_free(epidemic_url);
}
MSH_CMD_EXPORT(epidemic, Webclient get epidemic file);
//下载文件会中断，还不知道什么原因
