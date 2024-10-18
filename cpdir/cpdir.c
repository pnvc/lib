#define _XOPEN_SOURCE 500
#include <cpdir.h>
#include <sys/stat.h>
#include <ftw.h>
#include <errno.h>
#include <unistd.h>

#define STATIC_DEST_LEN 256

static char static_dest[STATIC_DEST_LEN];
static unsigned short static_dest_len = 0;
static unsigned short static_src_len = 0;
static struct s_cpdir_err static_errs;

static int nftw_cb(const char *path, const struct stat *stat,
		int type, struct FTW *ftw);

static int ts_creat_dir_ignore_umask(const char *path, mode_t mode, uid_t u,
		gid_t g);

static int prepare_static_vars(const char *dest, const char *src);

int cpdirmmap(const char *dest, const char *src, mode_t mode,
		struct s_cpdir_err *errs)
{
	cpdir_err err = CPDIR_ERR_OK;

	if (!errs)
		return CPDIR_ERR_ERRS_PTR;

	if (mode > 0777) {
		err = CPDIR_ERR_MODE_VALUE;
		goto end;
	}

	static_errs.errdir = CPDIR_ERR_OK;
	static_errs.errfil = CPFIL_ERR_OK;

	err = prepare_static_vars(dest, src);
	if (err)
		goto end;

	err = nftw(src, nftw_cb, 0, 0);

end:
	static_errs.errdir = err;

	errs->errfil = static_errs.errfil;
	errs->errdir = static_errs.errdir;

	return static_errs.errfil + static_errs.errdir;
}

static int nftw_cb(const char *path, const struct stat *stat,
		int type, struct FTW *ftw)
{
	cpdir_err errdir = CPDIR_ERR_OK;
	cpfil_err errfil = CPFIL_ERR_OK;
	char *d;
	const char *s;

	d = static_dest + static_dest_len;
	s = path + static_src_len;
	while (*s)
		*d++ = *s++;
	*d = 0;

	switch (type) {
	case FTW_D:
		errdir = ts_creat_dir_ignore_umask(static_dest,
				stat->st_mode, stat->st_uid, stat->st_gid);
		break;
	case FTW_F:
		errfil = cpfilmmap(static_dest, path);
		if (errfil) {
			errdir = CPDIR_ERR_CPFILMMAP;
			static_errs.errfil = errfil;
		}
		break;
	}

	return errdir;
}

static int ts_creat_dir_ignore_umask(const char *path, mode_t mode, uid_t u,
		gid_t g)
{
	if (mkdir(path, mode) < 0 && errno != EEXIST)
		return CPDIR_ERR_MKDIR;

	if (chmod(path, mode) < 0)
		return CPDIR_ERR_CHMOD;

	if (chown(path, u, g) < 0)
		return CPDIR_ERR_CHOWN;

	return CPDIR_ERR_OK;
}

static int prepare_static_vars(const char *dest, const char *src)
{
	unsigned short i;

	if (!dest)
		return CPDIR_ERR_DEST;

	if (!src)
		return CPDIR_ERR_SRC;

	while (dest[static_dest_len])
		static_dest_len++;
	while (src[static_src_len])
		static_src_len++;
	
	if (!static_dest_len || static_dest_len > STATIC_DEST_LEN)
		return CPDIR_ERR_DEST_LEN;

	if (!static_src_len || static_src_len > STATIC_DEST_LEN)
		return CPDIR_ERR_SRC_LEN;

	for (i = 0; i < static_dest_len; i++)
		static_dest[i] = dest[i];

	if (static_dest[static_dest_len - 1] != '/') {
		static_dest[static_dest_len] = '/';
		static_dest_len++;
		static_dest[static_dest_len] = 0;
	}

	if (src[static_src_len - 1] != '/')
		static_src_len++;

	return CPDIR_ERR_OK;
}

#undef _XOPEN_SOURCE

