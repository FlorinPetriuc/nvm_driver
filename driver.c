#include "driver.h"

int test_ioctl(const char *file_name)
{
	struct nvm *api = ioctl_init(file_name);

	if(!api)
	{
		PRINT_ERROR("ioctl_init");

		return 1;
	}

	if(ioctl_test(api))
	{
		PRINT_ERROR("ioctl_test");

		return 1;
	}

	ioctl_clean(api);

	return 0;
}

int test_write(const char *file_name)
{
	int i;

	int fd;

	char data[4096];

	for(i = 0; i < 4096; ++i)
	{
		data[i] = 't';
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

int main(void)
{
	const char *file_name = "/dev/test";

	if(test_ioctl(file_name))
	{
		PRINT_ERROR("ioctl error");

		return 1;
	}

	PRINT("write start");

	if(test_write(file_name))
	{
		PRINT_ERROR("write error");

		return 1;
	}

	PRINT("read start");

	if(test_read(file_name))
	{
		PRINT_ERROR("read error");

		return 1;
	}

	PRINT("SUCCESS");

	return 0;
}
