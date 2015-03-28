#ifndef _LIGHTNVM_IOCTL_H_
#define _LIGHTNVM_IOCTL_H_

typedef unsigned long long sector_t;

struct nvm_channel
{
	unsigned int gran_write;
	unsigned int gran_read;
	unsigned int gran_erase;
};

struct nvm_user_api_lun_channel
{
        unsigned long int lun_idx;
        unsigned short int chnl_idx;

        unsigned int gran_write;
        unsigned int gran_read;
        unsigned int gran_erase;
};

struct nvm_lun
{
	unsigned long nr_blocks;

	unsigned long nr_pages_per_blk;

	unsigned short int nchannels;

	struct nvm_channel *channels;
};

struct nvm_descriptor
{
	unsigned long nr_luns;

	struct nvm_lun *luns;
};

struct nvm_api_block
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
#define NVMCHANNELSNRGET    21533

#endif
