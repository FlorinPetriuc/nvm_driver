#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUG_ENABLED

#ifdef DEBUG_ENABLED

#define PRINT(x, ...) 		printf("INFO %s:%s - %d " x "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PRINT_ERROR(x, ...) printf("ERROR %s:%s - %d " x " : %s\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__, strerror(errno))

#else

#define PRINT(x, ...)
#define PRINT_ERROR(x, ...)

#endif

#endif
