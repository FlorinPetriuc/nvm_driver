#ifndef _RW_H_
#define _RW_H_

int rw_init(const char *file_name);
int do_write(const int file, const char *data, const int data_len);
int do_read(const int file, char *data, const int len);

void do_clean(const int file);

FILE *stream_init(const char *file_name, const char *mode);
int do_stream_write(FILE *file, const char *data);
int do_stream_read(FILE *file, char *data, const int len);

void do_stream_clean(FILE *file);

#endif
