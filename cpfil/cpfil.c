#include <cpfil.h>
#include <getfd.h>
#include <msg.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/user.h>

enum cpfilmmap_err {
	ERR_OK = 0,
	ERR_DEST,
	ERR_SRC,
	ERR_FD_DEST,
	ERR_FD_SRC,
	ERR_STAT_SRC,
	ERR_MMAP_SRC,
	ERR_MSGFD,
	ERR_COPY_LEN
};

#define PTR_TO_PAGE_MUL(x) (void*)((unsigned long)x >> PAGE_SHIFT << PAGE_SHIFT)
int cpfilmmap(const char *dest, const char *src)
{
	enum cpfilmmap_err err = ERR_OK;
	int fd_dest = 0, fd_src = 0;
	char *mmap_src = (char *)0;
	struct stat stat_src;
	ssize_t msg_ret;
	int saved_errno;

	if (!dest)
		return ERR_DEST;
	if (!src)
		return ERR_SRC;

	fd_dest = getfd_cwt(dest);
	if (fd_dest < 0)
		return ERR_FD_DEST;

	fd_src = getfd_r(src);
	if (fd_src < 0) {
		close(fd_dest);
		return ERR_FD_SRC;
	}

	if (fstat(fd_src, &stat_src) < 0) {
		close(fd_dest);
		close(fd_src);
		return ERR_STAT_SRC;
	}

	mmap_src = (char *)mmap(NULL, stat_src.st_size, PROT_READ, MAP_PRIVATE,
			fd_src, 0);
	if (mmap_src == MAP_FAILED) {
		close(fd_dest);
		close(fd_src);
		return ERR_MMAP_SRC;
	}

	msg_ret = msgfd(fd_dest, mmap_src, stat_src.st_size);
	if (msg_ret < 0) {
		saved_errno = errno;
		err = ERR_MSGFD;
	} else if (msg_ret < stat_src.st_size)
		err = ERR_COPY_LEN;

	munmap(PTR_TO_PAGE_MUL(mmap_src), stat_src.st_size);
	close(fd_dest);
	close(fd_src);

	errno = saved_errno;
	return err;
}
#undef PTR_TO_PAGE_MUL
