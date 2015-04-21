#ifndef _IOCTL_H_
#define _IOCTL_H_

#define NVMBLOCKPUT         21525
#define NVMBLOCKRRGET       21526
#define NVMLUNSNRGET        21527
#define NVMBLOCKSNRGET      21528
#define NVMBLOCKERASE       21529
#define NVMPAGESNRGET       21530
#define NVMBLOCKGETBYADDR   21531
#define NVMPAGESIZEGET      21532
#define NVMCHANNELSNRGET    21533

int ioctl_init(const char *file);
int ioctl_ops_test(const int fd);

void ioctl_clean(const int fd);

#endif
