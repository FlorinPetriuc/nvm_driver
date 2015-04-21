#ifndef _RW_H_
#define _RW_H_

FILE *rw_init(const char *file_name, const char *mode);
int do_write(FILE *file, const char *data);

void do_clean(FILE *file);

#endif
