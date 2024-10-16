#include <msg.h>

ssize_t msgfd(int fd, const char *m, ssize_t s)
{
	size_t i = 0;
	ssize_t wr, wr2 = 0;

	if (!m || !m[i])
		return 0;

	if (s > 0) {
		wr = write(fd, m, s);

		if (wr < 0)
			return wr;

		if (wr >= 0 && wr < s)
			wr2 = write(fd, m + wr, s - wr);
	} else {
		if (s < 0)
			m = m - s;

		if (!m[i])
			return 0;

		while (m[i])
			i++;

		wr = write(fd, m, i);

		if (wr < 0)
			return wr;

		if (wr >= 0 && wr < i)
			wr2 = write(fd, m + wr, i - wr);
	}

	if (wr2 < 0)
		return wr2;

	return wr + wr2;
}

ssize_t rmsgfd(int fd, char *b, ssize_t s)
{
	int rr;
	rr = read(fd, b, s);
	if (rr < s)
		b[rr] = 0;
	return rr;
}

#ifndef LIBINLINE
ssize_t msg(const char *m, ssize_t s) { return msgfd(1, m, s); }
ssize_t msgerr(const char *m, ssize_t s) { return msgfd(2, m, s); }
ssize_t rmsg(char *b, ssize_t s) { return rmsgfd(0, b, s); }
#endif /* INLINE */
