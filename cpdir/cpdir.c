#define _XOPEN_SOURCE 500
#include <cpdir.h>
#include <cpfil.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>

typedef enum {
	ERR_OK = 0,
	ERR_DEST,
	ERR_SRC,
	ERR_MKDIR,
	ERR_CHMOD,
} cpdirmmap_err;

static char static_dest[512];
static int dest_len = 0
static int src_len = 0;

static int nftw_cb(const char *path, const struct stat *stat,
		int type, struct FTW *ftw);

int cpdirmmap(const char *dest, const char *src)
{
	cpdirmmap_err err = ERR_OK;
	int i = 0;

	if (!dest)
		return ERR_DEST;

	if (!src)
		return ERR_SRC;

	// danger moment start
	while (dest[i] && i < 512) {
		static_dest[i] = dest[i];
		i++;
	}
	dest_len = i;
	i = 0;
	while (src[i])
		i++;
	src_len = i;
	// danger moment end

	if (mkdir(static_dest, 0755) < 0)
		return ERR_MKDIR;

	if (chmod(static_dest, 0775) < 0)
		return ERR_CHMOD;

	err = nftw(src, nftw_cb, 10, FTW_DEPTH);

	return (int)err;
}

static int nftw_cb(const char *path, const struct stat *stat,
		int type, struct FTW *ftw)
{
	int i = dest_len;
	char *src = path + ftw->base;

	while (src[i] && i < 512) {
		static_dest[i] = src[i];
		i++;
	}

	static_dest[i] = 0;

	switch (type) {
	case FTW_D:
	case FTW_DP:
		break;
	case FTW_F:
	}

	return 0;
}
#undef _XOPEN_SOURCE
