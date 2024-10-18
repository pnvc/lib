#ifndef GETFD_H_SENTRY
#define GETFD_H_SENTRY

#include <fcntl.h>
#include <sys/stat.h>

#ifdef LIBINLINE
#include <_getfd.h>
static inline int getfd_w(const char *n)
{ return open(n, O_WRONLY); }

static inline int getfd_r(const char *n)
{ return open(n, O_RDONLY); }

static inline int getfd_a(const char *n)
{ return open(n, O_APPEND); }

static inline int getfd_cw(const char *n)
{ return ts_creat_ignore_umask(n, O_CREAT | O_WRONLY, 436); }

static inline int getfd_ca(const char *n)
{ return ts_creat_ignore_umask(n, O_CREAT | O_APPEND, 436); }

static inline int getfd_cwt(const char *n)
{ return ts_creat_ignore_umask(n, O_CREAT | O_WRONLY | O_TRUNC, 436); }

static inline int getfd_cwtm(const char *n, mode_t mode)
{ return ts_creat_ignore_umask(n, O_CREAT | O_WRONLY | O_TRUNC, mode); }

static inline int getfd_cwtmug(const char *n, struct stat *s)
{ return ts_creat_ignore_umask_ug(n, O_CREAT | O_WRONLY | O_TRUNC, s); }

static inline int getfdat_w(int dfd, const char *n)
{ return openat(dfd, n, O_WRONLY); }

static inline int getfdat_r(int dfd, const char *n)
{ return openat(dfd, n, O_RDONLY); }

static inline int getfdat_a(int dfd, const char *n)
{ return openat(dfd, n, O_APPEND); }

static inline int getfdat_cw(int dfd, const char *n)
{ return ts_creat_at_ignore_umask(dfd, n, O_CREAT | O_WRONLY, 436); }

static inline int getfdat_ca(int dfd, const char *n)
{ return ts_creat_at_ignore_umask(dfd, n, O_CREAT | O_APPEND, 436); }

static inline int getfdat_cwt(int dfd, const char *n)
{ return ts_creat_at_ignore_umask(dfd, n, O_CREAT | O_WRONLY | O_TRUNC, 436); }
#else
int getfd_w(const char *);
int getfd_r(const char *);
int getfd_a(const char *);
int getfd_cw(const char *);
int getfd_ca(const char *);
int getfd_cwt(const char *);
int getfd_cwtm(const char *, mode_t);
int getfd_cwtmug(const char *, struct stat *);
int getfdat_w(int, const char *);
int getfdat_r(int, const char *);
int getfdat_a(int, const char *);
int getfdat_cw(int, const char *);
int getfdat_cwt(int, const char *);
int getfdat_ca(int, const char *);
#endif /* LIBINLINE */

#endif /* GETFD_H_SENTRY */
