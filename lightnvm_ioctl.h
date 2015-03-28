#ifndef _LIGHTNVM_IOCTL_H_
#define _LIGHTNVM_IOCTL_H_

typedef unsigned long long sector_t;

struct block_descriptor
{
	unsigned long nr_blocks;

	unsigned long nr_pages_per_blk;

	unsigned long page_size;
};

struct nvm_descriptor
{
	unsigned long nr_luns;

	struct block_descriptor *blk_desc;
};

struct nvm_user_block
{
    unsigned long lun;

    sector_t phys_addr;

    unsigned long id;

    void *internals;
};

#define NVMBLOCKPUT         21525
#define NVMBLOCKRRGET       21526
#define NVMLUNSNRGET        21527
#define NVMBLOCKSNRGET      21528
#define NVMBLOCKERASE       21529
#define NVMPAGESNRGET       21530
#define NVMBLOCKGETBYADDR   21531
#define NVMPAGESIZEGET      21532

#endif
