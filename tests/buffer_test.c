#include "../driver.h"

int test_write(const char *file_name)
{
	int i;

	int fd;

	char data[4096];

	for(i = 0; i < 4096; ++i)
	{
		data[i] = 'b';
	}

	fd = rw_init(file_name);

	if(fd < 0)
	{
		PRINT_ERROR("rw init error");

		return 1;
	}

	if(do_write(fd, data, 4096))
	{
		PRINT_ERROR("rw write error");

		return 1;
	}

	do_clean(fd);

	return 0;
}

int test_read(const char *file_name)
{
	int fd;

	char data[4097];

	int i;

	for(i = 0; i < 4097; ++i)
	{
		data[i] = 'u';
	}

	fd = rw_init(file_name);

	if(fd < 0)
	{
		PRINT_ERROR("rw init error");

		return 1;
	}

	if(do_read(fd, data, 4096))
	{
		PRINT_ERROR("rw read error");

		return 1;
	}
	data[4096] = '\0';

	PRINT("GOT %s", data);

	do_clean(fd);

	return 0;
}
