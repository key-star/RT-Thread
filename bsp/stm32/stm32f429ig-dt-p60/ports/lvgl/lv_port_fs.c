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
#include "lvgl.h"
#include "ff.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef FIL file_t;
typedef DIR dir_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void fs_init(void);

static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p);
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw);
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t fs_size(lv_fs_drv_t * drv, void * file_p, uint32_t * size_p);
static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);

static void * fs_dir_open(lv_fs_drv_t * drv, const char *path);
static lv_fs_res_t fs_dir_read(lv_fs_drv_t * drv, void * rddir_p, char * fn);
static lv_fs_res_t fs_dir_close(lv_fs_drv_t * drv, void * rddir_p);

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
     * Register the file system interface in LVGL
     *--------------------------------------------------*/
    
    if (dev_conf_status[SDIO_SD_INDEX] == 1 && dev_conf_status[SPI_FLASH_INDEX] == 1)
    return;

    /*Add a simple drive to open images*/
    static lv_fs_drv_t fs_drv[2];
    lv_fs_drv_init(&fs_drv[SDIO_SD_INDEX]);
    lv_fs_drv_init(&fs_drv[SPI_FLASH_INDEX]);

    /*Set up fields...*/
    fs_drv[SDIO_SD_INDEX].letter = 'S';
    fs_drv[SDIO_SD_INDEX].open_cb = fs_open;
    fs_drv[SDIO_SD_INDEX].close_cb = fs_close;
    fs_drv[SDIO_SD_INDEX].read_cb = fs_read;
    fs_drv[SDIO_SD_INDEX].write_cb = fs_write;
    fs_drv[SDIO_SD_INDEX].seek_cb = fs_seek;
    fs_drv[SDIO_SD_INDEX].tell_cb = fs_tell;

    fs_drv[SDIO_SD_INDEX].dir_close_cb = fs_dir_close;
    fs_drv[SDIO_SD_INDEX].dir_open_cb = fs_dir_open;
    fs_drv[SDIO_SD_INDEX].dir_read_cb = fs_dir_read;

    lv_fs_drv_register(&fs_drv[SDIO_SD_INDEX]);

    /*Set up fields...*/
    fs_drv[SPI_FLASH_INDEX].letter = 'F';
    fs_drv[SPI_FLASH_INDEX].open_cb = fs_open;
    fs_drv[SPI_FLASH_INDEX].close_cb = fs_close;
    fs_drv[SPI_FLASH_INDEX].read_cb = fs_read;
    fs_drv[SPI_FLASH_INDEX].write_cb = fs_write;
    fs_drv[SPI_FLASH_INDEX].seek_cb = fs_seek;
    fs_drv[SPI_FLASH_INDEX].tell_cb = fs_tell;

    fs_drv[SPI_FLASH_INDEX].dir_close_cb = fs_dir_close;
    fs_drv[SPI_FLASH_INDEX].dir_open_cb = fs_dir_open;
    fs_drv[SPI_FLASH_INDEX].dir_read_cb = fs_dir_read;

    lv_fs_drv_register(&fs_drv[SPI_FLASH_INDEX]);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your Storage device and File system.*/
static void fs_init(void)
{
    /*E.g. for FatFS initialize the SD card and FatFS itself*/

    /*You code here*/
}

/**
 * Open a file
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
 * @param mode      read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return          a file descriptor or NULL on error
 */
static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    char path_buf[128] = { 0 };
    uint8_t flags = 0;
    
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
		    return NULL;
	}

    if(mode == LV_FS_MODE_WR)
    {
        /*Open a file for write*/
        flags = FA_WRITE | FA_OPEN_ALWAYS;
    }
    else if(mode == LV_FS_MODE_RD)
    {
        /*Open a file for read*/
        flags = FA_READ;
    }
    else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
    {
        /*Open a file for read and write*/
        flags = FA_READ | FA_WRITE | FA_OPEN_ALWAYS;
    }

    FIL *fd = lv_mem_alloc(sizeof(FIL));
    if(fd == NULL) return NULL;

    FRESULT fres = f_open(fd, (const TCHAR*)path_buf, flags);
    if(fres == FR_OK)
    {
        res = LV_FS_RES_OK;
        return fd;
    }
    else
    {
        lv_mem_free(fd);
        rt_kprintf("f_open error (%d)\n", fres);
        res = LV_FS_RES_NOT_IMP;
        return NULL;
    }
}

/**
 * Close an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p)
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

    return res;
}

/**
 * Read data from an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param buf       pointer to a memory block where to store the read data
 * @param btr       number of Bytes To Read
 * @param br        the real number of read bytes (Byte Read)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
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

    return res;
}

/**
 * Write into a file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable
 * @param buf       pointer to a buffer with the bytes to write
 * @param btr       Bytes To Write
 * @param br        the number of real written bytes (Bytes Written). NULL if unused.
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
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

    return res;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open )
 * @param pos       the new position of read write pointer
 * @param whence    tells from where to interpret the `pos`. See @lv_fs_whence_t
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
    FRESULT fres;

    switch(whence)
    {
        case LV_FS_SEEK_SET:
            fres = f_lseek((FIL *)file_p, pos);
        break;

        case LV_FS_SEEK_CUR:
            fres = f_lseek(file_p, f_tell((FIL *)file_p) + pos);
        break;

        case LV_FS_SEEK_END:
            fres = f_lseek(file_p, f_size((FIL *)file_p) + pos);
        break;

        default:
            break;
    }

    if(fres != FR_OK)
	{
		rt_kprintf("f_lseek error (%d)\n", fres);
		res = LV_FS_RES_NOT_IMP;
	}
	else
	{
		res = LV_FS_RES_OK;
	}
    return res;
}
/**
 * Give the position of the read write pointer
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param pos_p     pointer to to store the result
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    *pos_p = f_tell((FIL *)file_p);
	res = LV_FS_RES_OK;

    return res;
}

/**
 * Initialize a 'lv_fs_dir_t' variable for directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to a directory
 * @return          pointer to the directory read descriptor or NULL on error
 */
static void * fs_dir_open(lv_fs_drv_t * drv, const char *path)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
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
		    return NULL;
	}

    DIR * dir = lv_mem_alloc(sizeof(DIR));
    if(dir == NULL) return NULL;

    FRESULT fres = f_opendir(dir, (const TCHAR*)path_buf);
    if(fres != FR_OK)
    {
        lv_mem_free(dir);
        dir = NULL;
        res = LV_FS_RES_NOT_IMP;
    }
    else
    {
        res = LV_FS_RES_OK;
    }

    return dir;
}

/**
 * Read the next filename form a directory.
 * The name of the directories will begin with '/'
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @param fn        pointer to a buffer to store the filename
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_read(lv_fs_drv_t * drv, void * rddir_p, char *fn)
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

    return res;
}

/**
 * Close the directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_close(lv_fs_drv_t * drv, void * rddir_p)
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

    return res;
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
