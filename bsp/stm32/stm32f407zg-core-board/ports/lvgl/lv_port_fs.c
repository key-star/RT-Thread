/**
 * @file lv_port_fs.c
 *
 */

 /*Copy this file as "lv_port_fs.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_fs.h"
#include "ff.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/* Create a type to store the required data about your file.
 * If you are using a File System library
 * it already should have a File type.
 * For example FatFS has `FIL`. In this case use `typedef FIL file_t`*/
//typedef struct {
//    /*Add the data you need to store about a file*/
//    uint32_t dummy1;
//    uint32_t dummy2;
//}file_t;

///*Similarly to `file_t` create a type for directory reading too */
//typedef struct {
//    /*Add the data you need to store about directory reading*/
//    uint32_t dummy1;
//    uint32_t dummy2;
//}dir_t;

typedef FIL file_t;
typedef DIR dir_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void fs_init(void);

static lv_fs_res_t fs_open (lv_fs_drv_t * drv, void * file_p, const char * path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close (lv_fs_drv_t * drv, void * file_p);
static lv_fs_res_t fs_read (lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw);
static lv_fs_res_t fs_seek (lv_fs_drv_t * drv, void * file_p, uint32_t pos);
static lv_fs_res_t fs_size (lv_fs_drv_t * drv, void * file_p, uint32_t * size_p);
static lv_fs_res_t fs_tell (lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);
static lv_fs_res_t fs_remove (lv_fs_drv_t * drv, const char *path);
static lv_fs_res_t fs_trunc (lv_fs_drv_t * drv, void * file_p);
static lv_fs_res_t fs_rename (lv_fs_drv_t * drv, const char * oldname, const char * newname);
static lv_fs_res_t fs_free (lv_fs_drv_t * drv, uint32_t * total_p, uint32_t * free_p);
static lv_fs_res_t fs_dir_open (lv_fs_drv_t * drv, void * rddir_p, const char *path);
static lv_fs_res_t fs_dir_read (lv_fs_drv_t * drv, void * rddir_p, char *fn);
static lv_fs_res_t fs_dir_close (lv_fs_drv_t * drv, void * rddir_p);

/**********************
 *  STATIC VARIABLES
 **********************/
FATFS*  fs_lv[2] = {NULL, NULL};
FRESULT fr_lv[2] = {FR_NOT_READY, FR_NOT_READY};
static uint8_t dev_conf_status[2] = {0, 0};

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/
#define SDIO_SD_INDEX   0
#define SPI_FLASH_INDEX 1

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_fs_init(void)
{
    /*----------------------------------------------------
     * Initialize your storage device and File System
     * -------------------------------------------------*/
    fs_init();

    /*---------------------------------------------------
     * Register the file system interface  in LVGL
     *--------------------------------------------------*/
    if (dev_conf_status[SDIO_SD_INDEX] == 1 && dev_conf_status[SPI_FLASH_INDEX] == 1)
    return;

    /* Add a simple drive to open images */
    lv_fs_drv_t fs_drv[2];
    lv_fs_drv_init(&fs_drv[SDIO_SD_INDEX]);
	lv_fs_drv_init(&fs_drv[SPI_FLASH_INDEX]);

    /*Set up fields...*/
    fs_drv[SDIO_SD_INDEX].file_size = sizeof(file_t);
    fs_drv[SDIO_SD_INDEX].letter = 'S';
    fs_drv[SDIO_SD_INDEX].open_cb = fs_open;
    fs_drv[SDIO_SD_INDEX].close_cb = fs_close;
    fs_drv[SDIO_SD_INDEX].read_cb = fs_read;
    fs_drv[SDIO_SD_INDEX].write_cb = fs_write;
    fs_drv[SDIO_SD_INDEX].seek_cb = fs_seek;
    fs_drv[SDIO_SD_INDEX].tell_cb = fs_tell;
    fs_drv[SDIO_SD_INDEX].free_space_cb = fs_free;
    fs_drv[SDIO_SD_INDEX].size_cb = fs_size;
    fs_drv[SDIO_SD_INDEX].remove_cb = fs_remove;
    fs_drv[SDIO_SD_INDEX].rename_cb = fs_rename;
    fs_drv[SDIO_SD_INDEX].trunc_cb = fs_trunc;

    fs_drv[SDIO_SD_INDEX].rddir_size = sizeof(dir_t);
    fs_drv[SDIO_SD_INDEX].dir_close_cb = fs_dir_close;
    fs_drv[SDIO_SD_INDEX].dir_open_cb = fs_dir_open;
    fs_drv[SDIO_SD_INDEX].dir_read_cb = fs_dir_read;

    lv_fs_drv_register(&fs_drv[SDIO_SD_INDEX]);
	
	
	fs_drv[SPI_FLASH_INDEX].file_size = sizeof(file_t);
    fs_drv[SPI_FLASH_INDEX].letter = 'F';
    fs_drv[SPI_FLASH_INDEX].open_cb = fs_open;
    fs_drv[SPI_FLASH_INDEX].close_cb = fs_close;
    fs_drv[SPI_FLASH_INDEX].read_cb = fs_read;
    fs_drv[SPI_FLASH_INDEX].write_cb = fs_write;
    fs_drv[SPI_FLASH_INDEX].seek_cb = fs_seek;
    fs_drv[SPI_FLASH_INDEX].tell_cb = fs_tell;
    fs_drv[SPI_FLASH_INDEX].free_space_cb = fs_free;
    fs_drv[SPI_FLASH_INDEX].size_cb = fs_size;
    fs_drv[SPI_FLASH_INDEX].remove_cb = fs_remove;
    fs_drv[SPI_FLASH_INDEX].rename_cb = fs_rename;
    fs_drv[SPI_FLASH_INDEX].trunc_cb = fs_trunc;

    fs_drv[SPI_FLASH_INDEX].rddir_size = sizeof(dir_t);
    fs_drv[SPI_FLASH_INDEX].dir_close_cb = fs_dir_close;
    fs_drv[SPI_FLASH_INDEX].dir_open_cb = fs_dir_open;
    fs_drv[SPI_FLASH_INDEX].dir_read_cb = fs_dir_read;

    lv_fs_drv_register(&fs_drv[SPI_FLASH_INDEX]);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/* Initialize your Storage device and File system. */
static void fs_init(void)
{
    /*E.g. for FatFS initalize the SD card and FatFS itself*/
	
//	fatfs_dev_init();
//	
//	if(fr_lv != FR_OK)
//	{
//		fr_lv = f_mount(fs_lv, "SPIF:", 1);
//		if(fr_lv != FR_OK)
//		{
//			rt_kprintf("spi flash mount error. (fr: %d)\n", fr_lv);
//		}
//		rt_kprintf("spi flash mount successfully.\n\n");
//	}
//	
//	if(fr_lv == FR_OK)
//	{
//		sd_show_card_info();
//	}
//	
//	if(fr_lv == FR_OK)
//	{
//		extern w25qxx_feature_s w25qxx;
//		rt_kprintf("SPI FLASH:\n");
//		rt_kprintf("Capacity : %d Bytes\nJEDECID  : %X\n", w25qxx.capacity, w25qxx.JEDECID);
//	}
    /*You code here*/
}

/**
 * Open a file
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable
 * @param path path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
 * @param mode read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_open (lv_fs_drv_t * drv, void * file_p, const char * path, lv_fs_mode_t mode)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
    
    char path_buf[128] = { 0 };
	uint8_t opt_mode = 0;
	
	//根据传入的参数判断是什么存储设备
	switch(drv->letter)
	{
		case 'S':       // SD card
			rt_sprintf(path_buf, "1:/%s", path);
		break;
		
		case 'F':       // SPI FALSH
			rt_sprintf(path_buf, "0:/%s", path);
		break;
		
		default:
			rt_kprintf("No drive %c\n", drv->letter);
		    res = LV_FS_RES_NOT_EX;
		    return res;
	}
	
	if(mode == LV_FS_MODE_WR)
    {
        /*Open a file for write*/
		opt_mode = FA_OPEN_ALWAYS | FA_WRITE;
        /* Add your code here*/
    }
    else if(mode == LV_FS_MODE_RD)
    {
        /*Open a file for read*/
		opt_mode = FA_OPEN_EXISTING | FA_READ;
        /* Add your code here*/
    }
    else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
    {
        /*Open a file for read and write*/
		opt_mode = FA_WRITE | FA_READ;
        /* Add your code here*/
    }
	
	FRESULT fres = f_open((FIL*)file_p, (const TCHAR*)path_buf, opt_mode);
	if(fres != FR_OK)
	{
		rt_kprintf("f_open error (%d)\n", fres);
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		res = LV_FS_RES_OK;
	}
	
	return res;
}


/**
 * Close an opened file
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable. (opened with lv_ufs_open)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_close (lv_fs_drv_t * drv, void * file_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	if(f_close((FIL*)file_p) != FR_OK)
	{
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		res = LV_FS_RES_OK;
	}
    /* Add your code here*/
	
    return res;
}

/**
 * Read data from an opened file
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable.
 * @param buf pointer to a memory block where to store the read data
 * @param btr number of Bytes To Read
 * @param br the real number of read bytes (Byte Read)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_read (lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	FRESULT fres = f_read((FIL*)file_p, buf, btr, br);
    if(fres != FR_OK)
	{
		rt_kprintf("f_read error (%d)\n", fres);
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		res = LV_FS_RES_OK;
	}
    /* Add your code here*/

    return res;
}

/**
 * Write into a file
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable
 * @param buf pointer to a buffer with the bytes to write
 * @param btr Bytes To Write
 * @param br the number of real written bytes (Bytes Written). NULL if unused.
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	FRESULT fres = f_write((FIL*)file_p, buf, btw, bw);
	if(fres != FR_OK)
	{
		rt_kprintf("f_write error (%d)\n", fres);
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		res = LV_FS_RES_OK;
	}
    /* Add your code here*/

    return res;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable. (opened with lv_ufs_open )
 * @param pos the new position of read write pointer
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek (lv_fs_drv_t * drv, void * file_p, uint32_t pos)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	FRESULT fres = f_lseek((FIL*)file_p, pos);
	if(fres != FR_OK)
	{
		rt_kprintf("f_lseek error (%d)\n", fres);
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		res = LV_FS_RES_OK;
	}
    /* Add your code here*/

    return res;
}

/**
 * Give the size of a file bytes
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable
 * @param size pointer to a variable to store the size
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_size (lv_fs_drv_t * drv, void * file_p, uint32_t * size_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	*size_p = f_size((FIL*)file_p);
	res = LV_FS_RES_OK;
    /* Add your code here*/

    return res;
}
/**
 * Give the position of the read write pointer
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable.
 * @param pos_p pointer to to store the result
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_tell (lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	*pos_p = f_tell((FIL*)file_p);
	res = LV_FS_RES_OK;
    /* Add your code here*/

    return res;
}

/**
 * Delete a file
 * @param drv pointer to a driver where this function belongs
 * @param path path of the file to delete
 * @return  LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_remove (lv_fs_drv_t * drv, const char *path)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	FRESULT fres = FR_INVALID_PARAMETER;
    char path_buf[256] = {0};
	
	//根据传入的参数判断是什么存储设备
	switch(drv->letter)
	{
		case 'S':       // SD card
			rt_sprintf(path_buf, "1:/%s", path);
		break;
		
		case 'F':       // SPI FALSH
			rt_sprintf(path_buf, "0:/%s", path);
		break;
		
		default:
			rt_kprintf("No drive %c\n", drv->letter);
		    res = LV_FS_RES_NOT_EX;
		    return res;
	}
	
	fres = f_unlink((const TCHAR*)path_buf);
	if(fres != FR_OK)
	{
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		res = LV_FS_RES_OK;
	}
    /* Add your code here*/

    return res;
}

/**
 * Truncate the file size to the current position of the read write pointer
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to an 'ufs_file_t' variable. (opened with lv_fs_open )
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_trunc (lv_fs_drv_t * drv, void * file_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	if(f_truncate((FIL*)file_p) != FR_OK)
	{
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		res = LV_FS_RES_OK;
	}
    /* Add your code here*/

    return res;
}

/**
 * Rename a file
 * @param drv pointer to a driver where this function belongs
 * @param oldname path to the file
 * @param newname path with the new name
 * @return LV_FS_RES_OK or any error from 'fs_res_t'
 */
static lv_fs_res_t fs_rename (lv_fs_drv_t * drv, const char * oldname, const char * newname)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	FRESULT fres = FR_INVALID_PARAMETER;
    char path_old_buf[256] = {0};
	char path_new_buf[256] = {0};
	
	//根据传入的参数判断是什么存储设备
	switch(drv->letter)
	{
		case 'S':       // SD card
			rt_sprintf(path_old_buf, "1:/%s", oldname);
		    rt_sprintf(path_new_buf, "1:/%s", newname);
		break;
		
		case 'F':       // SPI FALSH
			rt_sprintf(path_old_buf, "0:/%s", oldname);
		    rt_sprintf(path_new_buf, "0:/%s", newname);
		break;
		
		default:
			rt_kprintf("No drive %c\n", drv->letter);
		    res = LV_FS_RES_NOT_EX;
		    return res;
	}
	
	fres = f_rename((const TCHAR*)path_old_buf, (const TCHAR*)path_new_buf);
	if(fres != FR_OK)
	{
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		res = LV_FS_RES_OK;
	}
    /* Add your code here*/

    return res;
}

/**
 * Get the free and total size of a driver in kB
 * @param drv pointer to a driver where this function belongs
 * @param letter the driver letter
 * @param total_p pointer to store the total size [kB]
 * @param free_p pointer to store the free size [kB]
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_free (lv_fs_drv_t * drv, uint32_t * total_p, uint32_t * free_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	FRESULT fres = FR_INVALID_PARAMETER;
	FATFS*  fs1;
	
    char path_buf[10] = { 0 };
	uint32_t t_size = 0;
	uint32_t f_size = 0;
	DWORD free_clusters = 0;
	DWORD total_sector  = 0;
	DWORD free_sector   = 0;
	
	//根据传入的参数判断是什么存储设备
	switch(drv->letter)
	{
		case 'S':       // SD card
			strcpy(path_buf, "1:/");
		break;
		
		case 'F':       // SPI FALSH
			strcpy(path_buf, "0:/");
		break;
		
		default:
			rt_kprintf("No drive %c\n", drv->letter);
		    res = LV_FS_RES_NOT_EX;
		    return res;
	}
	
	//得到磁盘信息及空闲簇数量
	fres = f_getfree((const TCHAR*)path_buf, &free_clusters, &fs1);
	if(fres != FR_OK)
	{
		*total_p = 0;
		*free_p  = 0;
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		total_sector = (fs1->n_fatent - 2) * fs1->csize;   //得到总扇区数
		free_sector = free_clusters * fs1->csize;          //得到空闲扇区数
#if RT_DFS_ELM_MAX_SECTOR_SIZE != 512                  //扇区大小不是512字节,则转换为512字节
		total_sector *= fs1->ssize >> 9;
		free_sector  *= fs1->ssize >> 9;
#endif
		t_size = total_sector >> 1;    //单位为KB
		f_size = free_sector  >> 1;    //单位为KB
		
		*total_p = t_size;
		*free_p  = f_size;
		rt_kprintf("t_size: %d\tf_size: %d\n", t_size, f_size);
		res = LV_FS_RES_OK;
	}
    /* Add your code here*/

    return res;
}

/**
 * Initialize a 'fs_read_dir_t' variable for directory reading
 * @param drv pointer to a driver where this function belongs
 * @param rddir_p pointer to a 'fs_read_dir_t' variable
 * @param path path to a directory
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_open (lv_fs_drv_t * drv, void * rddir_p, const char *path)
{
	lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	FRESULT fres = FR_INVALID_PARAMETER;
    char path_buf[256] = {0};
	
	//根据传入的参数判断是什么存储设备
	switch(drv->letter)
	{
		case 'S':       // SD card
			rt_sprintf(path_buf, "1:/%s", path);
		break;
		
		case 'F':       // SPI FALSH
			rt_sprintf(path_buf, "0:/%s", path);
		break;
		
		default:
			rt_kprintf("No drive %c\n", drv->letter);
		    res = LV_FS_RES_NOT_EX;
		    return res;
	}
	
	fres = f_opendir((DIR*)rddir_p, (const TCHAR*)path_buf);
	if(fres != FR_OK)
	{
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		res = LV_FS_RES_OK;
	}
    /* Add your code here*/

    return res;
}

/**
 * Read the next filename form a directory.
 * The name of the directories will begin with '/'
 * @param drv pointer to a driver where this function belongs
 * @param rddir_p pointer to an initialized 'fs_read_dir_t' variable
 * @param fn pointer to a buffer to store the filename
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_read (lv_fs_drv_t * drv, void * rddir_p, char *fn)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	FRESULT fres = FR_INVALID_PARAMETER;
    FILINFO finfo;
	
	fres = f_readdir((DIR*)rddir_p, &finfo);
    if(fres != FR_OK)
	{
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		fn = finfo.fname;
		res = LV_FS_RES_OK;
	}
    /* Add your code here*/

    return res;
}

/**
 * Close the directory reading
 * @param drv pointer to a driver where this function belongs
 * @param rddir_p pointer to an initialized 'fs_read_dir_t' variable
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_close (lv_fs_drv_t * drv, void * rddir_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
	
	FRESULT fres = FR_INVALID_PARAMETER;
	
	fres = f_closedir((DIR*)rddir_p);
	if(fres != FR_OK)
	{
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		res = LV_FS_RES_OK;
	}
    /* Add your code here*/

    return res;
}

#else /* Enable this file at the top */

/* This dummy typedef exists purely to silence -Wpedantic. */
typedef int keep_pedantic_happy;
#endif
