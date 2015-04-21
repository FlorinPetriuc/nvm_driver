#include "../driver.h"

static struct nvm_descriptor nvm_d;

int ioctl_init(const char *file)
{
	int fd;
	int ret;

	unsigned long i;

	unsigned short int j;

	struct nvm_user_api_lun_channel chnl_desc;

	fd = open("/dev/test", O_RDWR);

	if (fd < 0)
	{
		PRINT_ERROR("");

		goto exit;
	}

	ret = ioctl(fd, NVMLUNSNRGET, &nvm_d.nr_luns);

	if(ret != 0)
	{
		PRINT_ERROR("%d", ret);

		goto exit;
	}

	PRINT("We have %lu luns", nvm_d.nr_luns);

	ALLOC_MEMORY(nvm_d.luns, nvm_d.nr_luns, struct nvm_lun);

	for(i = 0; i < nvm_d.nr_luns; ++i)
	{
		nvm_d.luns[i].nr_blocks = i;

		ret = ioctl(fd, NVMBLOCKSNRGET, &nvm_d.luns[i].nr_blocks);

		if(ret != 0)
		{
			PRINT_ERROR("%d", ret);

			goto exit;
		}

		PRINT("Lun %lu has %lu blocks", i, nvm_d.luns[i].nr_blocks);

		nvm_d.luns[i].nr_pages_per_blk = i;

		ret = ioctl(fd, NVMPAGESNRGET, &nvm_d.luns[i].nr_pages_per_blk);

		if(ret != 0)
		{
			PRINT_ERROR("%d", ret);

			goto exit;
		}

		PRINT("Lun %lu has %lu pages per block", i, nvm_d.luns[i].nr_pages_per_blk);

		nvm_d.luns[i].nchannels = i;

		ret = ioctl(fd, NVMCHANNELSNRGET, &nvm_d.luns[i].nchannels);

		if(ret != 0)
		{
			PRINT_ERROR("%d", ret);

			goto exit;
		}

		PRINT("Lun %lu has %hu channels", i, nvm_d.luns[i].nchannels);

		ALLOC_MEMORY(nvm_d.luns[i].channels, nvm_d.luns[i].nchannels, struct nvm_channel);

		chnl_desc.lun_idx = i;

		for(j = 0; j < nvm_d.luns[i].nchannels; ++j)
		{
			chnl_desc.chnl_idx = j;

			ret = ioctl(fd, NVMPAGESIZEGET, &chnl_desc);

			if(ret != 0)
			{
				PRINT_ERROR("%d", ret);

				goto exit;
			}

			nvm_d.luns[i].channels[j].gran_erase = chnl_desc.gran_erase;
			nvm_d.luns[i].channels[j].gran_read = chnl_desc.gran_read;
			nvm_d.luns[i].channels[j].gran_write = chnl_desc.gran_write;

			PRINT("Lun %lu channel %hu has %u writes %u reads and %u erase", i, nvm_d.luns[i].nchannels,
																				nvm_d.luns[i].channels[j].gran_write,
																				nvm_d.luns[i].channels[j].gran_read,
																				nvm_d.luns[i].channels[j].gran_erase);
		}
	}

exit:
	if(ret)
	{
		close(fd);

		return -1;
	}

	return fd;
}

int ioctl_ops_test(const int fd)
{
	int ret;

	unsigned long i;

	struct nvm_api_block block;

	for(i = 0; i < nvm_d.nr_luns; ++i)
	{
		block.lun = i;

		ret = ioctl(fd, NVMBLOCKRRGET, &block);

		if(ret != 0)
		{
			PRINT_ERROR("%d", ret);

			goto exit;
		}

		PRINT("Got RR block %lu", block.id);

		ret = ioctl(fd, NVMBLOCKPUT, &block);

		if(ret != 0)
		{
			PRINT_ERROR("%d", ret);

			goto exit;
		}

		PRINT("Put block");

		ret = ioctl(fd, NVMBLOCKERASE, &block);

		if(ret != 0)
		{
			PRINT_ERROR("%d", ret);

			goto exit;
		}

		PRINT("Erase block");
	}

exit:
	return ret;

}

void ioctl_clean(const int fd)
{
	unsigned long i;

	close(fd);

	for(i = 0; i < nvm_d.nr_luns; ++i)
	{
		free(nvm_d.luns[i].channels);
	}
	free(nvm_d.luns);
}
