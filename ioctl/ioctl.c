#include "../driver.h"

struct nvm *ioctl_init(const char *file)
{
	struct nvm *api = NULL;

	int ret;

	unsigned long i;
	unsigned long j;

	struct nba_channel chnl_desc;

	ALLOC_MEMORY(api, 1, struct nvm);

	api->fd = open("/dev/test", O_RDWR);

	if (api->fd < 0)
	{
		PRINT_ERROR("");

		goto err;
	}

	ret = ioctl(api->fd, NVMLUNSNRGET, &api->nr_luns);

	if(ret != 0)
	{
		PRINT_ERROR("%d", ret);

		goto err;
	}

	PRINT("We have %lu luns", api->nr_luns);

	ALLOC_MEMORY(api->luns, api->nr_luns, struct nvm_lun);

	for(i = 0; i < api->nr_luns; ++i)
	{
		api->luns[i].nr_blocks = i;

		ret = ioctl(api->fd, NVMBLOCKSNRGET, &api->luns[i].nr_blocks);

		if(ret != 0)
		{
			PRINT_ERROR("%d", ret);

			goto err;
		}

		PRINT("Lun %lu has %lu blocks", i, api->luns[i].nr_blocks);

		ALLOC_MEMORY(api->luns[i].blocks, api->luns[i].nr_blocks, struct nvm_block);

		for(j = 0; j < api->luns[i].nr_blocks; ++j)
		{
			api->luns[i].blocks[j].id = j;
			api->luns[i].blocks[j].lun = i;

			ret = ioctl(api->fd, NVMBLOCKGETBYID, &api->luns[i].blocks[j]);

			//PRINT("Block %lu has physical address %llu", j, api->luns[i].blocks[j].phys_addr);
		}

		api->luns[i].nr_pages_per_blk = i;

		ret = ioctl(api->fd, NVMPAGESNRGET, &api->luns[i].nr_pages_per_blk);

		if(ret != 0)
		{
			PRINT_ERROR("%d", ret);

			goto err;
		}

		PRINT("Lun %lu has %lu pages per block", i, api->luns[i].nr_pages_per_blk);

		api->luns[i].nchannels = i;

		ret = ioctl(api->fd, NVMCHANNELSNRGET, &api->luns[i].nchannels);

		if(ret != 0)
		{
			PRINT_ERROR("%d", ret);

			goto err;
		}

		PRINT("Lun %lu has %hu channels", i, api->luns[i].nchannels);

		ALLOC_MEMORY(api->luns[i].channels, api->luns[i].nchannels, struct nvm_channel);

		chnl_desc.lun_idx = i;

		for(j = 0; j < api->luns[i].nchannels; ++j)
		{
			chnl_desc.chnl_idx = j;

			ret = ioctl(api->fd, NVMPAGESIZEGET, &chnl_desc);

			if(ret != 0)
			{
				PRINT_ERROR("%d", ret);

				goto err;
			}

			api->luns[i].channels[j].gran_erase = chnl_desc.gran_erase;
			api->luns[i].channels[j].gran_read = chnl_desc.gran_read;
			api->luns[i].channels[j].gran_write = chnl_desc.gran_write;

			PRINT("Lun %lu channel %hu has %u writes %u reads and %u erase", i, api->luns[i].nchannels,
																				api->luns[i].channels[j].gran_write,
																				api->luns[i].channels[j].gran_read,
																				api->luns[i].channels[j].gran_erase);
		}
	}

	return api;

err:
	if(api)
	{
		close(api->fd);

		free(api);

		return NULL;
	}

	return NULL;
}

int ioctl_test(struct nvm *api)
{
	unsigned long block_id;

	unsigned long lun_id;

	struct nvm_block test_block;

	int ret;
	int test_cnt;

	for(test_cnt = 0; test_cnt < 10; ++test_cnt)
	{
		lun_id = rand() % api->nr_luns;
		block_id = rand() % api->luns[lun_id].nr_blocks;

		test_block.lun = lun_id;
		test_block.phys_addr = api->luns[lun_id].blocks[block_id].phys_addr;

		ret = ioctl(api->fd, NVMBLOCKGETBYADDR, &test_block);

		if(ret)
		{
			PRINT_ERROR("");
			goto err;
		}

		if(test_block.id != block_id)
		{
			PRINT_ERROR("%lu vs %lu", block_id, test_block.id);
			goto err;
		}
	}

	return 0;

err:
	return 1;
}

void ioctl_clean(struct nvm *api)
{
	unsigned long i;

	if(!api)
	{
		return;
	}

	close(api->fd);

	if(api->nr_luns > 0)
	{
		for(i = 0; i < api->nr_luns; ++i)
		{
			free(api->luns[i].channels);
		}
		free(api->luns);
	}

	free(api);
}
