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

FILE *stream_init(const char *file_name, const char *mode)
{
	FILE *ret;

	ret = fopen(file_name, mode);

	if(!ret)
	{
		PRINT_ERROR("");
	}

	return ret;
}

int do_stream_write(FILE *file, const char *data)
{
	if(fseek(file, 0, SEEK_SET) != 0)
	{
		goto err;
	}

	if(fputs(data, file) == EOF)
	{
		goto err;
	}

	return 0;

err:
	do_stream_clean(file);

	PRINT_ERROR("");

	return 1;
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

int do_stream_read(FILE *file, char *data, const int len)
{
	if(fseek(file, 0, SEEK_SET) != 0)
	{
		goto err;
	}

	if(fgets(data, len, file) == NULL)
	{
		goto err;
	}
	data[len - 1] = '\0';

	return 0;

err:
	do_stream_clean(file);

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

void do_stream_clean(FILE *file)
{
	pclose(file);
}
