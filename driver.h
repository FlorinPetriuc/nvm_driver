#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#include "debug/debug.h"
#include "util/mem.h"
#include "util/typedefs.h"
#include "driver.h"
#include "ioctl/ioctl.h"
#include "rw/rw.h"
#include "tests/buffer_test.h"
#include "tests/stream_test.h"
#include "tests/ioctl_test.h"

#endif
