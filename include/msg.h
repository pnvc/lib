#ifndef MSG_H_SENTRY
#define MSG_H_SENTRY 1

#include "err.h"

ssize_t msgfd(int fd, const char *buf, ssize_t buf_size, S_ERR);
ssize_t rmsgfd(int fd, char *buf, ssize_t bus_size, S_ERR);

/*
#ifdef LIBINLINE
static inline ssize_t msg(const char *m, ssize_t s) { return msgfd(1, m, s); }
static inline ssize_t msgerr(const char *m, ssize_t s) { return msgfd(2, m, s); }
static inline ssize_t rmsg(char *b, ssize_t s) { return rmsgfd(0, b, s); }
#else
ssize_t msg(const char *m, ssize_t s);
ssize_t msgerr(const char *, ssize_t);
ssize_t rmsg(char *, ssize_t);
#endif  LIBINLINE */

#endif /* MSG_H_SENTRY */
