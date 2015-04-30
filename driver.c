#include "driver.h"

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
