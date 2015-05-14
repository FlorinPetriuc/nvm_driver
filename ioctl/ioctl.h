#ifndef _IOCTL_H_
#define _IOCTL_H_

#define NVMBLOCKPUT         21525
#define NVMBLOCKRRGET       21526
#define NVMLUNSNRGET        21527
#define NVMBLOCKSNRGET      21528
#define NVMBLOCKERASE       21529
#define NVMPAGESNRGET       21530
#define NVMBLOCKGETBYADDR   21531
#define NVMBLOCKGETBYID	    21532
#define NVMPAGESIZEGET      21533
#define NVMCHANNELSNRGET    21534

struct nvm *ioctl_init(const char *file);

int ioctl_get_test(struct nvm *api);

int ioctl_erase_all(struct nvm *api);

void ioctl_clean(struct nvm *api);

#endif
