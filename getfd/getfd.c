#include <getfd.h>
#include <_getfd.h>

int getfd_w(const char *n)
{ return open(n, O_WRONLY); }

int getfd_r(const char *n)
{ return open(n, O_RDONLY); }

int getfd_a(const char *n)
{ return open(n, O_APPEND); }

int getfd_cw(const char *n)
{ return ts_creat_ignore_umask(n, O_CREAT | O_WRONLY, 0664); }

int getfd_ca(const char *n)
{ return ts_creat_ignore_umask(n, O_CREAT | O_APPEND, 0664); }

int getfd_cwt(const char *n)
{ return ts_creat_ignore_umask(n, O_CREAT | O_WRONLY | O_TRUNC, 0664); }

int getfd_cwtm(const char *n, mode_t mode)
{ return ts_creat_ignore_umask(n, O_CREAT | O_WRONLY | O_TRUNC, mode); }

int getfd_cwtmug(const char *n, struct stat *s)
{ return ts_creat_ignore_umask_ug(n, O_CREAT | O_WRONLY | O_TRUNC, s); }

int getfdat_w(int dfd, const char *n)
{ return openat(dfd, n, O_WRONLY); }

int getfdat_r(int dfd, const char *n)
{ return openat(dfd, n, O_RDONLY); }

int getfdat_a(int dfd, const char *n)
{ return openat(dfd, n, O_APPEND); }

int getfdat_cw(int dfd, const char *n)
{ return ts_creat_at_ignore_umask(dfd, n, O_CREAT | O_WRONLY, 0664); }

int getfdat_ca(int dfd, const char *n)
{ return ts_creat_at_ignore_umask(dfd, n, O_CREAT | O_APPEND, 0664); }

int getfdat_cwt(int dfd, const char *n)
{ return ts_creat_at_ignore_umask(dfd, n, O_CREAT | O_WRONLY | O_TRUNC, 0664); }
