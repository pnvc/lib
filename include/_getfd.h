#ifndef _GETFD_H_SENTRY
#define _GETFD_H_SENTRY

#include <unistd.h>

static inline int ts_creat_ignore_umask(const char *n, int f, mode_t m)
{
	int fd;
	fd = open(n, f, m);
	if (fd < 0)
		return -1;
	if (fchmod(fd, m) < 0)
		return -2;
	return fd;
}

static inline int ts_creat_ignore_umask_ug(const char *n, int f, struct stat *s)
{
	int fd;
	fd = open(n, f, s->st_mode);
	if (fd < 0)
		return -1;
	if (fchmod(fd, s->st_mode) < 0)
		return -2;
	if (fchown(fd, s->st_uid, s->st_gid) < 0)
		return -3;
	return fd;
}

static inline int ts_creat_at_ignore_umask(int dfd, const char *n, int f,
		mode_t m)
{
	int fd;
	fd = openat(dfd, n, f, m);
	if (fd < 0)
		return -1;
	if (fchmod(fd, m) < 0)
		return -2;
	return fd;
}

#endif /* _GETFD_H_SENTRY */
