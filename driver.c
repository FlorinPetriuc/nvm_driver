#include "driver.h"

int main(void)
{
	int fd;

	char data[100];

	FILE *test;

	const char *file_name = "/dev/test";

	fd = ioctl_init(file_name);

	if(fd < 0)
	{
		PRINT_ERROR("ioctl_init");

		goto RW_OPS;
	}

	ioctl_ops_test(fd);
	ioctl_clean(fd);

RW_OPS:

	test = rw_init("/dev/test", "w");

	if(test == NULL)
	{
		goto exit;
	}

	if(do_write(test, "t"))
	{
		goto exit;
	}

	do_clean(test);

	test = rw_init("/dev/test", "r");

	if(test == NULL)
	{
		goto exit;
	}

	if(do_read(test, data, 100))
	{
		goto exit;
	}

	do_clean(test);

	PRINT("ENDING %s", data);

exit:
	return 0;
}
