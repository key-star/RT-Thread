#include "ftp.h"

#if defined(PKG_USING_AGILE_FTP)

static int agile_ftp_init(void)
{
	ftp_init(2048, 27, 100);
	
	return RT_EOK;
}
INIT_ENV_EXPORT(agile_ftp_init);
#endif
