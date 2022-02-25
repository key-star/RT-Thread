#include "dfs_fs.h"

#ifdef RT_USING_DFS_MNTTABLE
const struct dfs_mount_tbl mount_table[] =
{
    {"W25Q128", "/", "elm", 0, 0},
    {0}
};
#endif
