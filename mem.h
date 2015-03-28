#ifndef MEM_H_
#define MEM_H_

#define ALLOC_MEMORY(x, y, z) \
(x) = (z *)malloc((y) * sizeof(z));\
if(!(x))\
{\
	printf("out of memory\n");\
	exit(EXIT_FAILURE);\
}

#endif /* MEM_H_ */
