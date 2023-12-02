#ifndef __LIBPOSIX_RENICE_H
#define __LIBPOSIX_RENICE_H

#include <Macros.h>
#include "types.h"

extern C pid_t renicepid(pid_t pid, int *stat_loc, int newPriority, int options);

#endif /* __LIBPOSIX_RENICE_H */
