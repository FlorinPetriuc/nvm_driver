#ifndef _RW_H_
#define _RW_H_

int rw_init(const char *file_name);
int do_write(const int file, const char *data, const int data_len);

void do_clean(const int file);

#endif
