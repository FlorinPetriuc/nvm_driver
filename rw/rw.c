#include "../driver.h"

FILE *rw_init(const char *file_name, const char *mode)
{
	FILE *ret;

	ret = popen(file_name, mode);

	if(ret == NULL)
	{
		PRINT_ERROR("");
	}

	return ret;
}

int do_write(FILE *file, const char *data)
{
	if(fputs(data, file) == EOF)
	{
		PRINT("");

		do_clean(file);

		PRINT_ERROR("");

		return 1;
	}

	return 0;
}

int do_read(FILE *file, char *data, const int len)
{
	if(fgets(data, len, file) == NULL)
	{
		do_clean(file);

		PRINT_ERROR("");

		return 1;
	}
	data[len - 1] = '\0';

	return 0;
}

void do_clean(FILE *file)
{
	pclose(file);
}
