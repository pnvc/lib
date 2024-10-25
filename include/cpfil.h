#ifndef CPFIL_H_SENTRY
#define CPFIL_H_SENTRY

typedef enum {
	CPFIL_ERR_OK = 0,
	CPFIL_ERR_DEST,
	CPFIL_ERR_SRC,
	CPFIL_ERR_FD_DEST,
	CPFIL_ERR_FD_SRC,
	CPFIL_ERR_STAT_SRC,
	CPFIL_ERR_MMAP_SRC,
	CPFIL_ERR_MSGFD,
	CPFIL_ERR_COPY_LEN
} cpfil_err;

int cpfilmmap(const char *dest, const char *src);
int cpfil(const char *dest, const char *src);

#endif /* CPFIL_H_SENTRY */
