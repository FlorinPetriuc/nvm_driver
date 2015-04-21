#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

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

#endif
