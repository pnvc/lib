#include <cpfil.h>
#include <getfd.h>
#include <msg.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/user.h>

int cpfilmmap(const char *dest, const char *src)
{
	cpfil_err err = CPFIL_ERR_OK;
	int fd_dest = 0, fd_src = 0;
	char *mmap_src = (char *)0;
	struct stat stat_src;
	ssize_t msg_ret;
	int saved_errno = 0;

	if (!dest)
		return CPFIL_ERR_DEST;
	if (!src)
		return CPFIL_ERR_SRC;

	fd_src = getfd_r(src);
	if (fd_src < 0)
		return CPFIL_ERR_FD_SRC;

	if (fstat(fd_src, &stat_src) < 0) {
		close(fd_src);
		return CPFIL_ERR_STAT_SRC;
	}

	fd_dest = getfd_cwtm(dest, stat_src.st_mode);
	if (fd_dest < 0) {
		close(fd_src);
		return CPFIL_ERR_FD_DEST;
	}

	if (stat_src.st_size) {
		mmap_src = (char *)mmap(NULL, stat_src.st_size, PROT_READ,
				MAP_PRIVATE, fd_src, 0);
		if (mmap_src == MAP_FAILED) {
			close(fd_dest);
			close(fd_src);
			return CPFIL_ERR_MMAP_SRC;
		}
	
		msg_ret = msgfd(fd_dest, mmap_src, stat_src.st_size);
		if (msg_ret < 0) {
			saved_errno = errno;
			err = CPFIL_ERR_MSGFD;
		} else if (msg_ret < stat_src.st_size)
			err = CPFIL_ERR_COPY_LEN;

		munmap((void *)((unsigned long)mmap_src & 
					~(sysconf(_SC_PAGE_SIZE) - 1)),
				stat_src.st_size);
	}

	close(fd_dest);
	close(fd_src);

	if (saved_errno)
		errno = saved_errno;

	return (int)err;
}
