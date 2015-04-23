#include "../driver.h"

int rw_init(const char *file_name)
{
	int ret;

	ret = open(file_name, O_RDWR);

	if(ret < 0)
	{
		PRINT_ERROR("");
	}

	return ret;
}

int do_write(const int file, const char *data, const int data_len)
{
	if(lseek(file, 0, SEEK_SET) != 0)
	{
		goto err;
	}

	if(write(file, data, data_len) < 0)
	{
		goto err;
	}

	return 0;

err:
	do_clean(file);

	PRINT_ERROR("");

	return 1;
}

int do_read(const int file, char *data, const int len)
{
	if(lseek(file, 0, SEEK_SET) != 0)
	{
		goto err;
	}

	if(read(file, data, len) < 0)
	{
		goto err;
	}
	data[len - 1] = '\0';

	return 0;

err:
	do_clean(file);

	PRINT_ERROR("");

	return 1;
}

void do_clean(const int file)
{
	close(file);
}
