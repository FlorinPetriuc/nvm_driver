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
	struct nvm_user_block block;

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
		return 1;
	}

	printf("We have %lu luns\n", nvm_d.nr_luns);

	ALLOC_MEMORY(nvm_d.blk_desc, nvm_d.nr_luns, struct block_descriptor);

	for(i = 0; i < nvm_d.nr_luns; ++i)
	{
		nvm_d.blk_desc[i].nr_blocks = i;

		ret = ioctl(fd, NVMBLOCKSNRGET, &nvm_d.blk_desc[i].nr_blocks);

		if(ret != 0)
		{
			printf("ioctl returned error: %d\n", ret);
			goto exit;
		}

		printf("Lun %lu has %lu blocks\n", i, nvm_d.blk_desc[i].nr_blocks);

		nvm_d.blk_desc[i].nr_pages_per_blk = i;

		ret = ioctl(fd, NVMPAGESNRGET, &nvm_d.blk_desc[i].nr_pages_per_blk);

		if(ret != 0)
		{
			printf("ioctl returned error: %d\n", ret);
			goto exit;
		}

		printf("Lun %lu has %lu pages per block\n", i, nvm_d.blk_desc[i].nr_pages_per_blk);

		nvm_d.blk_desc[i].page_size = i;

		ret = ioctl(fd, NVMPAGESIZEGET, &nvm_d.blk_desc[i].page_size);

		if(ret != 0)
		{
			printf("ioctl returned error: %d\n", ret);
			goto exit;
		}

		printf("Lun %lu has %lu page size\n", i, nvm_d.blk_desc[i].page_size);
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

		for(j = 0; j < nvm_d.blk_desc[i].nr_blocks; ++j)
		{
			ret = ioctl(fd, NVMBLOCKGETBYADDR, &block);

			if(ret != 0)
			{
				break;
			}

			block.phys_addr += (sector_t)nvm_d.blk_desc[i].nr_pages_per_blk;
			printf("Got addr block %lu\n", block.id);
		}
	}

exit:
	close(fd);
	free(nvm_d.blk_desc);

	return 0;
}
