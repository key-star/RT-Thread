/*
 * File      : olympic_sample.c
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
#include <cJSON.h>
#include <finsh.h>
#include "dfs_posix.h"

#define GET_HEADER_BUFSZ        1024        //头部大小
#define GET_RESP_BUFSZ          25 * 1024    //响应缓冲区大小
#define GET_URL_LEN_MAX         256         //网址最大长度
#define GET_URI                 "http://act.e.mi.com/olympic/medal_rank"
#define FILE_BUFSZ              3 * 1024

typedef struct
{
	cJSON *country_name;
	cJSON *rank;
	cJSON *country_flag;
	cJSON *gold;
    cJSON *silver;
    cJSON *bronze;
	cJSON *count;
    cJSON *update_time;
}medal_obj;

medal_obj medals[10];

/* 奥运奖牌数据解析 */
void olympic_data_parse(rt_uint8_t *data)
{
    cJSON *root = RT_NULL, *data_obj = RT_NULL, *list_obj = RT_NULL;
	
    root = cJSON_Parse((const char *)data);
    if (!root)
    {
        rt_kprintf("No memory for cJSON root!\n");
        return;
    }

    data_obj = cJSON_GetObjectItem(root, "data");
	
    int size = cJSON_GetArraySize(data_obj);
    for(int idx = 0; idx < size; idx++)
    {
        list_obj = cJSON_GetArrayItem(data_obj, idx);
		
		medals[idx].country_name = cJSON_GetObjectItem(list_obj, "country_name");
		medals[idx].rank         = cJSON_GetObjectItem(list_obj, "rank");
		medals[idx].country_flag = cJSON_GetObjectItem(list_obj, "country_flag");
		medals[idx].gold         = cJSON_GetObjectItem(list_obj, "medal_gold_count");
		medals[idx].silver       = cJSON_GetObjectItem(list_obj, "medal_silver_count");
		medals[idx].bronze       = cJSON_GetObjectItem(list_obj, "medal_bronze_count");
		medals[idx].count        = cJSON_GetObjectItem(list_obj, "medal_sum_count");
		medals[idx].update_time  = cJSON_GetObjectItem(list_obj, "update_time");
		
		rt_kprintf("country name:%s,rank:%s,gold:%s,silver:%s,bronze:%s,count:%s,update time:%s\n",
                   medals[idx].country_name->valuestring, medals[idx].rank->valuestring, medals[idx].gold->valuestring,
				   medals[idx].silver->valuestring, medals[idx].bronze->valuestring,
				   medals[idx].count->valuestring, medals[idx].update_time->valuestring);
    }
	
	if (root != RT_NULL)
        cJSON_Delete(root);
}

void olympic(int argc, char **argv)
{
    rt_uint8_t *buffer = RT_NULL;
    int resp_status;
    struct webclient_session *session = RT_NULL;
    char *olympic_url = RT_NULL;
    int content_length = -1, bytes_read = 0;
    int content_pos = 0;
	
    /* 为 olympic_url 分配空间 */
    olympic_url = rt_calloc(1, GET_URL_LEN_MAX);
    if (olympic_url == RT_NULL)
    {
        rt_kprintf("No memory for olympic_url!\n");
        goto __exit;
    }
	
    /* 拼接 GET 网址 */
	rt_snprintf(olympic_url, GET_URL_LEN_MAX, GET_URI);
	
    /* 创建会话并且设置响应的大小 */
    session = webclient_session_create(GET_HEADER_BUFSZ);
    if (session == RT_NULL)
    {
        rt_kprintf("No memory for get header!\n");
        goto __exit;
    }

    /* 发送 GET 请求使用默认的头部 */
    if ((resp_status = webclient_get(session, olympic_url)) != 200)
    {
        rt_kprintf("webclient GET request failed, response(%d) error.\n", resp_status);
        goto __exit;
    }

    /* 分配用于存放接收数据的缓冲 */
    buffer = rt_calloc(1, GET_RESP_BUFSZ);
    if (buffer == RT_NULL)
    {
        rt_kprintf("No memory for data receive buffer!\n");
        goto __exit;
    }

    content_length = webclient_content_length_get(session);
    if (content_length < 0)
    {
        /* 返回的数据是分块传输的. */
        do
        {
            bytes_read = webclient_read(session, buffer, GET_RESP_BUFSZ);
            if (bytes_read <= 0)
            {
                break;
            }
        }while (1);
    }
    else
    {
        do
        {
            bytes_read = webclient_read(session, buffer,
                                        content_length - content_pos > GET_RESP_BUFSZ ?
                                        GET_RESP_BUFSZ : content_length - content_pos);
            if (bytes_read <= 0)
            {
                break;
            }
            content_pos += bytes_read;
        }while (content_pos < content_length);
    }

    /* 奥运奖牌数据解析 */
    olympic_data_parse(buffer);

__exit:
    /* 释放网址空间 */
    if (olympic_url != RT_NULL)
        rt_free(olympic_url);
    /* 关闭会话 */
    if (session != RT_NULL)
        webclient_close(session);
    /* 释放缓冲区空间 */
    if (buffer != RT_NULL)
        rt_free(buffer);
}
//MSH_CMD_EXPORT(olympic, Get olympic by webclient);
//接收文件较大，json解析时内存不够

void olympic_by_file(int argc, char **argv)
{
	int fd, size;
	rt_uint8_t *buffer = RT_NULL;
	
	buffer = rt_malloc(FILE_BUFSZ);
    if (buffer == RT_NULL)
    {
        rt_kprintf("No memory for data receive buffer!\n");
        goto __exit;
    }
	rt_memset(buffer, 0, FILE_BUFSZ);
	
	/* Open file in read-only mode */
    fd = open("/sdcard/olympic.json", O_RDONLY);
    if (fd >= 0)
    {
        size = read(fd, buffer, FILE_BUFSZ);
        close(fd);
		rt_kprintf("Read data from file olympic(size: %d)\n", size);
    }
	
	olympic_data_parse(buffer);
	
__exit:
    /* 释放缓冲区空间 */
    if (buffer != RT_NULL)
        rt_free(buffer);
}
MSH_CMD_EXPORT(olympic_by_file, Get olympic by local file);
