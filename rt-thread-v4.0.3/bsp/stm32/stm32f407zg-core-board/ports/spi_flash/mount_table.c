#include "fal.h"
#include "dfs_fs.h"
#include "dfs_posix.h"

#ifdef RT_USING_DFS_MNTTABLE
const struct dfs_mount_tbl mount_table[] =
{
    {"W25Q128", "/", "elm", 0, 0},
    {0}
};
#endif

#ifdef RT_USING_DFS_ELMFAT

#define FS_PARTITION_NAME  "filesystem"
#define BUF_SIZE 1024

int elmfat_mount(void)
{
    struct statfs elm_stat;
    struct fal_blk_device *blk_dev;
	
    /* fal init */
    fal_init();
	
    /* create block device */
    blk_dev = (struct fal_blk_device *)fal_blk_device_create(FS_PARTITION_NAME);
    if(blk_dev == RT_NULL)
	{
		rt_kprintf("Can't create a block device on '%s' partition.\n", FS_PARTITION_NAME);
		return -RT_ERROR;
	}
    else
	{
		rt_kprintf("Create a block device on the %s partition of flash successfully.\n", FS_PARTITION_NAME);
	}
	
	/* mount elmfat file system to FS_PARTITION_NAME */
	if(dfs_mount(FS_PARTITION_NAME, "/", "elm", 0, 0) == 0)
	{
		rt_kprintf("elmfat filesystem mount to '/' successfully.\n");
	}
	else
	{
		rt_kprintf("elmfat filesystem mount to '/' failed,now retrying.\n");
		
		/* make a elmfat format filesystem */
		if(dfs_mkfs("elm", FS_PARTITION_NAME) == 0)
		{
			rt_kprintf("make elmfat filesystem successfully.\n");
			rt_thread_delay(200);
			
			rt_kprintf("reboot now.\n");
			rt_hw_cpu_reset();
		}
		else
		{
			rt_kprintf("make elmfat filesystem failed.\n");
			return -RT_ERROR;
		}
	}
	
    /* get elmfat file system statistics */
    if(statfs("/", &elm_stat) == 0)
        rt_kprintf("elmfat filesystem block size: %d, total blocks: %d, free blocks: %d.\n", 
                    elm_stat.f_bsize, elm_stat.f_blocks, elm_stat.f_bfree);
	
	DIR *dirp;
//    struct dirent *d;
	
    /* open directory */
    dirp = opendir("/sdcard");
    if (dirp == RT_NULL)
    {
		if(mkdir("/sdcard", 0x777) == 0)
		{
			rt_kprintf("make a directory: '/sdcard' successfully.\n");
		}
		else
		{
			rt_kprintf("make a directory: '/sdcard' failed.\n");
			return -RT_ERROR;
		}
    }
    else
    {
        /* read directory */
//        while((d = readdir(dirp)) != RT_NULL)
//        {
//            rt_kprintf("found %s\n", d->d_name);
//        }
		
        /* close directory */
        closedir(dirp);
    }
	
	/* mount elmfat file system to sdcard */
	if(dfs_mount("sd0", "/sdcard", "elm", 0, 0) == 0)
	{
		rt_kprintf("elmfat filesystem mount to '/sdcard' successfully.\n");
	}
	else
	{
		rt_kprintf("elmfat filesystem mount to '/sdcard' failed,now retrying.\n");
		
		/* make a elmfat format filesystem */
		if(dfs_mkfs("elm", "sd0") == 0)
		{
			rt_kprintf("make elmfat filesystem to sdcard successfully.\n");
			rt_thread_delay(200);
			
			rt_kprintf("reboot now.\n");
			rt_hw_cpu_reset();
		}
		else
		{
			rt_kprintf("make elmfat filesystem to sdcard failed.\n");
			return -RT_ERROR;
		}
	}
	
    /* get elmfat file system statistics */
    if(statfs("/sdcard", &elm_stat) == 0)
        rt_kprintf("elmfat filesystem block size: %d, total blocks: %d, free blocks: %d.\n", 
                    elm_stat.f_bsize, elm_stat.f_blocks, elm_stat.f_bfree);
	
	return RT_EOK;
}
INIT_ENV_EXPORT(elmfat_mount);
#endif
