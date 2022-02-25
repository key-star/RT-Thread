#include "rtthread.h"
#include "rtdevice.h"
#include "board.h"
#include "fal.h"
#include "dfs_posix.h"

#define FS_PARTITION_NAME  "filesystem"
#define BUF_SIZE 1024

static int fal_test(const char *partiton_name)
{
    int ret;
    int i, j, len;
    uint8_t buf[BUF_SIZE];
    const struct fal_flash_dev *flash_dev = RT_NULL;
    const struct fal_partition *partition = RT_NULL;

    if (!partiton_name)
    {
        rt_kprintf("Input param partition name is null!\n");
        return -1;
    }

    partition = fal_partition_find(partiton_name);
    if (partition == RT_NULL)
    {
        rt_kprintf("Find partition (%s) failed!\n", partiton_name);
        ret = -1;
        return ret;
    }

    flash_dev = fal_flash_device_find(partition->flash_name);
    if (flash_dev == RT_NULL)
    {
        rt_kprintf("Find flash device (%s) failed!\n", partition->flash_name);
        ret = -1;
        return ret;
    }

    rt_kprintf("Flash device : %s   "
               "Flash size : %dK   \n"
               "Partition : %s   "
               "Partition size: %dK\n", 
                partition->flash_name, 
                flash_dev->len/1024,
                partition->name,
                partition->len/1024);

    /* erase all partition */
    ret = fal_partition_erase_all(partition);
    if (ret < 0)
    {
        rt_kprintf("Partition (%s) erase failed!\n", partition->name);
        ret = -1;
        return ret;
    }
    rt_kprintf("Erase (%s) partition finish!\n", partiton_name);

    /* read the specified partition and check data */
    for (i = 0; i < partition->len;)
    {
        rt_memset(buf, 0x00, BUF_SIZE);

        len = (partition->len - i) > BUF_SIZE ? BUF_SIZE : (partition->len - i);

        ret = fal_partition_read(partition, i, buf, len);
        if (ret < 0)
        {
            rt_kprintf("Partition (%s) read failed!\n", partition->name);
            ret = -1;
            return ret;
        }

        for(j = 0; j < len; j++)
        {
            if (buf[j] != 0xFF)
            {
                rt_kprintf("The erase operation did not really succeed!\n");
                ret = -1;
                return ret;
            }
        }
        i += len;
    }

    /* write 0x00 to the specified partition */
    for (i = 0; i < partition->len;)
    {
        rt_memset(buf, 0x00, BUF_SIZE);

        len = (partition->len - i) > BUF_SIZE ? BUF_SIZE : (partition->len - i);

        ret = fal_partition_write(partition, i, buf, len);
        if (ret < 0)
        {
            rt_kprintf("Partition (%s) write failed!\n", partition->name);
            ret = -1;
            return ret;
        }

        i += len;
    }
    rt_kprintf("Write (%s) partition finish! Write size %d(%dK).\n", partiton_name, i, i/1024);

    /* read the specified partition and check data */
    for (i = 0; i < partition->len;)
    {
        rt_memset(buf, 0xFF, BUF_SIZE);

        len = (partition->len - i) > BUF_SIZE ? BUF_SIZE : (partition->len - i);

        ret = fal_partition_read(partition, i, buf, len);
        if (ret < 0)
        {
            rt_kprintf("Partition (%s) read failed!\n", partition->name);
            ret = -1;
            return ret;
        }

        for(j = 0; j < len; j++)
        {
            if (buf[j] != 0x00)
            {
                rt_kprintf("The write operation did not really succeed!\n");
                ret = -1;
                return ret;
            }
        }

        i += len;
    }

    ret = 0;
    return ret;
}

static void fal_sample(void)
{
    /* 1- init */
    fal_init();

    if (fal_test("wifi_image") == 0)
    {
        rt_kprintf("Fal partition (%s) test success!\n", "wifi_image");
    }
    else
    {
        rt_kprintf("Fal partition (%s) test failed!\n", "wifi_image");
    }

    if (fal_test("download") == 0)
    {
        rt_kprintf("Fal partition (%s) test success!\n", "download");
    }
    else
    {
        rt_kprintf("Fal partition (%s) test failed!\n", "download");
    }
}
MSH_CMD_EXPORT(fal_sample, fal sample);

static void fal_elmfat_sample(void)
{
    int fd, size;
    struct statfs elm_stat;
    struct fal_blk_device *blk_dev;
    char str[] = "elmfat mount to W25Q128 flash.", buf[80];

    /* fal init */
    fal_init();

    /* create block device */
    blk_dev = (struct fal_blk_device *)fal_blk_device_create(FS_PARTITION_NAME);
    if(blk_dev == RT_NULL)
        rt_kprintf("Can't create a block device on '%s' partition.\n", FS_PARTITION_NAME);
    else
        rt_kprintf("Create a block device on the %s partition of flash successful.\n", FS_PARTITION_NAME);

    /* make a elmfat format filesystem */
    if(dfs_mkfs("elm", FS_PARTITION_NAME) == 0)
        rt_kprintf("make elmfat filesystem success.\n");

    /* mount elmfat file system to FS_PARTITION_NAME */
    if(dfs_mount(FS_PARTITION_NAME, "/", "elm", 0, 0) == 0)
        rt_kprintf("elmfat filesystem mount success.\n");

    /* Get elmfat file system statistics */
    if(statfs("/", &elm_stat) == 0)
        rt_kprintf("elmfat filesystem block size: %d, total blocks: %d, free blocks: %d.\n", 
                    elm_stat.f_bsize, elm_stat.f_blocks, elm_stat.f_bfree);

    if(mkdir("/user", 0x777) == 0)
        rt_kprintf("make a directory: '/user'.\n");

    rt_kprintf("Write string '%s' to /user/test.txt.\n", str);

    /* Open the file in create and read-write mode, create the file if it does not exist*/
    fd = open("/user/test.txt", O_WRONLY | O_CREAT);
    if (fd >= 0)
    {
        if(write(fd, str, sizeof(str)) == sizeof(str))
            rt_kprintf("Write data done.\n");

        close(fd);   
    }

    /* Open file in read-only mode */
    fd = open("/user/test.txt", O_RDONLY);
    if (fd >= 0)
    {
        size = read(fd, buf, sizeof(buf));

        close(fd);

        if(size == sizeof(str))
            rt_kprintf("Read data from file test.txt(size: %d): %s \n", size, buf);
    }
}
MSH_CMD_EXPORT_ALIAS(fal_elmfat_sample, fal_elmfat,fal elmfat sample);
