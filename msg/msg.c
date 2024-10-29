#include <msg.h>
#include <unistd.h>

#define prepare(rw) ssize_t retval = 0, ret##rw = 0; \
			errno = 0; \
			SET_ERR_OK

ssize_t msgfd(int fd, const char *buf, ssize_t buf_size, struct s_err *err)
{
	prepare(w);
	while (retw != buf_size) {
		retw = write(fd, buf + retval, (buf_size -= retval));
		if (retw < 0) {
			/* here u can modify return err type scenario
			 * for your programm */
			switch (errno) {
			case EFAULT:
				SET_ERR_CRIT; break;
			case EAGAIN:
			case EINTR:
			case EFBIG:
			case EPIPE:
			case EIO:
			case ENOSPC:
				SET_ERR_OKE; break;
			case EDESTADDRREQ:
			case EBADF:
			case EDQUOT:
			case EINVAL:
			case EPERM:
				SET_ERR; break;
			}
			return retval;
		}
		retval += retw;
	}
	return retval;
}

inline void msg(const char *buf) { write(1, buf, strlen(buf)); }
inline void msgerr(const char *buf) { write(2, buf, strlen(buf)); }

ssize_t rmsgfd(int fd, char *buf, ssize_t buf_size, struct s_err *err)
{
	prepare(r);
}
