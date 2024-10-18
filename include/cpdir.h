#ifndef CPDIR_H_SENTRY
#define CPDIR_H_SENTRY

#include <sys/types.h>
#include <cpfil.h>

typedef enum {
	CPDIR_ERR_OK = 0,
	CPDIR_ERR_DEST,
	CPDIR_ERR_SRC,
	CPDIR_ERR_MODE_VALUE,
	CPDIR_ERR_DEST_LEN,
	CPDIR_ERR_SRC_LEN,
	CPDIR_ERR_MKDIR,
	CPDIR_ERR_CHMOD,
	CPDIR_ERR_CPFILMMAP,
	CPDIR_ERR_ERRS_PTR,
	CPDIR_ERR_LSTAT,
	CPDIR_ERR_CHOWN
} cpdir_err;

struct s_cpdir_err {
	cpfil_err errfil;
	cpdir_err errdir;
};

int cpdirmmap(const char *dest, const char *src, mode_t mode,
		struct s_cpdir_err *errs);

#endif
