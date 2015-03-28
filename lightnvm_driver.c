#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#include "lightnvm_ioctl.h"
#include "mem.h"

int main(void)
{
	int fd;
	int ret;

	unsigned long i;
	unsigned long j;

	struct nvm_descriptor nvm_d;
	struct nvm_api_block block;
	struct nvm_user_api_lun_channel chnl_desc;

	fd = open("/dev/test", O_RDWR);

	if (fd < 0)
	{
		printf("error opening file\n");
		return 1;
	}

	ret = ioctl(fd, NVMLUNSNRGET, &nvm_d.nr_luns);

	if(ret != 0)
	{
		printf("ioctl returned error: %d\n", ret);
		goto exit;
	}

	printf("We have %lu luns\n", nvm_d.nr_luns);

	ALLOC_MEMORY(nvm_d.luns, nvm_d.nr_luns, struct nvm_lun);

	for(i = 0; i < nvm_d.nr_luns; ++i)
	{
		nvm_d.luns[i].nr_blocks = i;

		ret = ioctl(fd, NVMBLOCKSNRGET, &nvm_d.luns[i].nr_blocks);

		if(ret != 0)
		{
			printf("ioctl returned error: %d\n", ret);
			goto exit;
		}

		printf("Lun %lu has %lu blocks\n", i, nvm_d.luns[i].nr_blocks);

		nvm_d.luns[i].nr_pages_per_blk = i;

		ret = ioctl(fd, NVMPAGESNRGET, &nvm_d.luns[i].nr_pages_per_blk);

		if(ret != 0)
		{
			printf("ioctl returned error: %d\n", ret);
			goto exit;
		}

		printf("Lun %lu has %lu pages per block\n", i, nvm_d.luns[i].nr_pages_per_blk);

		nvm_d.luns[i].nchannels = i;

		ret = ioctl(fd, NVMCHANNELSNRGET, &nvm_d.luns[i].nchannels);

		if(ret != 0)
		{
			printf("ioctl returned error: %d\n", ret);
			goto exit;
		}

		printf("Lun %lu has %hu channels\n", i, nvm_d.luns[i].nchannels);

		ALLOC_MEMORY(nvm_d.luns[i].channels, nvm_d.luns[i].nchannels, struct nvm_channel);

		chnl_desc.lun_idx = i;

		for(j = 0; j < nvm_d.luns[i].nchannels; ++j)
		{
			chnl_desc.chnl_idx = j;

			ret = ioctl(fd, NVMPAGESIZEGET, &chnl_desc);

			if(ret != 0)
			{
				printf("ioctl returned error: %d\n", ret);
				goto exit;
			}

			nvm_d.luns[i].channels[j].gran_erase = chnl_desc.gran_erase;
			nvm_d.luns[i].channels[j].gran_read = chnl_desc.gran_read;
			nvm_d.luns[i].channels[j].gran_write = chnl_desc.gran_write;

			printf("Lun %lu channel %hu has %u writes %u reads and %u erase\n", i, 	nvm_d.luns[i].nchannels,
																					nvm_d.luns[i].channels[j].gran_write,
																					nvm_d.luns[i].channels[j].gran_read,
																					nvm_d.luns[i].channels[j].gran_erase);
		}
	}

	for(i = 0; i < nvm_d.nr_luns; ++i)
	{
		block.lun = i;

		ret = ioctl(fd, NVMBLOCKRRGET, &block);

		if(ret != 0)
		{
			printf("ioctl returned error: %d\n", ret);
			goto exit;
		}

		printf("Got RR block %lu\n", block.id);

		ret = ioctl(fd, NVMBLOCKPUT, &block);

		if(ret != 0)
		{
			printf("ioctl returned error: %d\n", ret);
			goto exit;
		}

		printf("Put block\n");

		ret = ioctl(fd, NVMBLOCKERASE, &block);

		if(ret != 0)
		{
			printf("ioctl returned error: %d\n", ret);
			goto exit;
		}

		printf("Erase block\n");
	}

	for(i = 0; i < nvm_d.nr_luns; ++i)
	{
		block.lun = i;
		block.phys_addr = 0;

		for(j = 0; j < nvm_d.luns[i].nr_blocks; ++j)
		{
			ret = ioctl(fd, NVMBLOCKGETBYADDR, &block);

			if(ret != 0)
			{
				break;
			}

			block.phys_addr += (sector_t)nvm_d.luns[i].nr_pages_per_blk;
			printf("Got addr block %lu\n", block.id);
		}
	}

	for(i = 0; i < nvm_d.nr_luns; ++i)
	{
		free(nvm_d.luns[i].channels);
	}
	free(nvm_d.luns);

exit:
	close(fd);

	return 0;
}
