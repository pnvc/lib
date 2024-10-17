#ifndef CPDIR_H_SENTRY
#define CPDIR_H_SENTRY

#include <sys/types.h>

int cpdirmmap(const char *dest, const char *src, mode_t mode);

#endif
