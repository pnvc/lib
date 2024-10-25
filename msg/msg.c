#include <msg.h>

ssize_t msgfd(int fd, const char *buf, ssize_t buf_size, S_ERR)
{
	ssize_t retval = 0;
	if (!buf) {
		errno = EFAULT;
		SET_ERR();
		return 0;
	}

	while (retval != buf_size) {
		retval = write(fd, buf + retval, (buf_size -= retval));
		if (retval < 0) {
			;
		}
	}
}

ssize_t rmsgfd(int fd, char *buf, ssize_t buf_size, S_ERR)
{
	int rr;
	rr = read(fd, b, s);
	if (rr < s)
		b[rr] = 0;
	return rr;
}
