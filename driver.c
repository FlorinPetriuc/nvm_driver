#include "driver.h"

static int work_info(const char *file_name)
{
	struct nvm *api;

	PRINT("ERASING ALL BLOCKS");

	api = ioctl_init(file_name);
	if(!api)
	{
		PRINT_ERROR("ioctl error");

		return 1;
	}
}

static int work_erase_all(const char *file_name)
{
	struct nvm *api;

	PRINT("ERASING ALL BLOCKS");

	api = ioctl_init(file_name);
	if(!api)
	{
		PRINT_ERROR("ioctl error");

		return 1;
	}

	if(ioctl_erase_all(api))
	{
		PRINT_ERROR("ioctl error");

		ioctl_clean(api);

		return 1;
	}

	ioctl_clean(api);

	PRINT("ERASE SUCCESS");

	return 0;
}

static int work_test_all(const char *file_name)
{
	PRINT("RUNNING TEST CASES");

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

	PRINT("BUFFER SUCCESS");

	PRINT("stream write start");

	if(test_write_stream(file_name))
	{
		PRINT_ERROR("write stream error");

		return 1;
	}

	PRINT("stream read start");

	if(test_read_stream(file_name))
	{
		PRINT_ERROR("read stream error");

		return 1;
	}

	PRINT("STREAM SUCCESS");

	return 0;
}

int main(int argc, char **argv)
{
	const char *file_name = "/dev/test";

	unsigned char do_clear = 0;
	unsigned char do_info = 0;
	unsigned char do_self_test = 0;

	int i;

	for(i = 1; i < argc; ++i)
	{
		if(strcmp(argv[i], "clear") == 0)
		{
			do_clear = 1;
		}
		else if(strcmp(argv[i], "test") == 0)
		{
			do_self_test = 1;
		}
		else if(strcmp(argv[i], "info") == 0)
		{
			do_info = 1;
		}
		else if(argv[i][0] == '/')
		{
			file_name = argv[i];
		}
	}

	PRINT("using %s", file_name);

	if(do_info)
	{
		if(work_info(file_name))
		{
			return 1;
		}
	}

	if(do_clear)
	{
		if(work_erase_all(file_name))
		{
			return 1;
		}
	}

	if(do_self_test)
	{
		if(work_test_all(file_name))
		{
			return 1;
		}
	}

	return 0;
}
