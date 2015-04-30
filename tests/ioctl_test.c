#include "../driver.h"

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
