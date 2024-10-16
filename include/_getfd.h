#ifndef _GETFD_H_SENTRY
#define _GETFD_H_SENTRY

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

static inline int ts_creat_at_ignore_umask(int dfd, const char *n, int f, mode_t m)
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
