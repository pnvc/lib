#ifndef MES_H_SENTRY
#define MES_H_SENTRY 1

#include <unistd.h>

ssize_t msgfd(int, const char *, ssize_t);
ssize_t rmsgfd(int, char *, ssize_t);

#ifdef LIBINLINE
static inline ssize_t msg(const char *m, ssize_t s) { return msgfd(1, m, s); }
static inline ssize_t msgerr(const char *m, ssize_t s) { return msgfd(2, m, s); }
static inline ssize_t rmsg(char *b, ssize_t s) { return rmsgfd(0, b, s); }
#else
ssize_t msg(const char *m, ssize_t s);
ssize_t msgerr(const char *, ssize_t);
ssize_t rmsg(char *, ssize_t);
#endif /* LIBINLINE */

#endif /* MES_H_SENTRY */
