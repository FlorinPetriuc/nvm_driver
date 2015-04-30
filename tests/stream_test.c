#include "../driver.h"

int test_write_stream(const char *file_name)
{
	int i;

	FILE *fd;

	char data[4097];

	for(i = 0; i < 4096; ++i)
	{
		data[i] = 't';
	}
	data[4096] = '\0';

	fd = stream_init(file_name, "w");

	if(!fd)
	{
		PRINT_ERROR("w stream init error");

		return 1;
	}

	if(do_stream_write(fd, data))
	{
		PRINT_ERROR("stream write error");

		return 1;
	}

	do_stream_clean(fd);

	return 0;
}

int test_read_stream(const char *file_name)
{
	FILE *fd;

	char data[4097];

	int i;

	for(i = 0; i < 4097; ++i)
	{
		data[i] = 'u';
	}

	fd = stream_init(file_name, "r");

	if(!fd)
	{
		PRINT_ERROR("stream init error");

		return 1;
	}

	if(do_stream_read(fd, data, 4096))
	{
		PRINT_ERROR("rw read error");

		return 1;
	}
	data[4096] = '\0';

	PRINT("GOT %s", data);

	do_stream_clean(fd);

	return 0;
}
