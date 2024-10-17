#define _XOPEN_SOURCE 700
#include <cpdir.h>
#include <cpfil.h>
#include <sys/stat.h>
#include <ftw.h>
#include <string.h>

#include <stdio.h> // debug

typedef enum {
	ERR_OK = 0,
	ERR_DEST,
	ERR_SRC,
	ERR_DEST_LEN,
	ERR_SRC_LEN,
	ERR_MKDIR,
	ERR_CHMOD,
	ERR_MKDIR_CB,
	ERR_CHMOD_CB,
} cpdirmmap_err;

#define STATIC_DEST_LEN 256

static char static_dest[STATIC_DEST_LEN];
static ssize_t static_dest_len = 0;
static ssize_t static_src_len = 0;
static mode_t static_mode = 0;

static int nftw_cb(const char *path, const struct stat *stat,
		int type, struct FTW *ftw);

int cpdirmmap(const char *dest, const char *src, mode_t mode)
{
	cpdirmmap_err err = ERR_OK;

	if (!dest)
		return ERR_DEST;

	if (!src)
		return ERR_SRC;

	static_dest_len = strlen(dest);
	static_src_len = strlen(src);
	
	if (static_dest_len > STATIC_DEST_LEN)
		return ERR_DEST;

	if (static_src_len > STATIC_DEST_LEN)
		return ERR_SRC;

	static_mode = mode;

	strcpy(static_dest, dest);

	if (mkdir(static_dest, mode) < 0)
		return ERR_MKDIR;

	if (chmod(static_dest, mode) < 0)
		return ERR_CHMOD;

	err = nftw(src, nftw_cb, 0, 0);

	return (int)err;
}

static int nftw_cb(const char *path, const struct stat *stat,
		int type, struct FTW *ftw)
{
	if (type == FTW_D) {
		printf("%s\n", path); // debug
		;
	} else if (type == FTW_F) {
		;
	}

	return 0;
}
#undef _XOPEN_SOURCE
