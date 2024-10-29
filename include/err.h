#ifndef ERR_H_SENTRY
#define ERR_H_SENTRY

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum {
	ERR_OK = 0,
	ERR,
	ERR_CRIT
} e_err;

struct s_err {
	int Errno;
	e_err err;
};

#define SET_ERR_TYPE(x)	err->err = x
#define SAVE_ERRNO	err->Errno = errno
#define NULL_ERRNO	err->Errno = 0

#define SET_ERR_CRIT	SET_ERR_TYPE(ERR_CRIT);	SAVE_ERRNO
#define SET_ERR		SET_ERR_TYPE(ERR);	SAVE_ERRNO
#define SET_ERR_OKE	SET_ERR_TYPE(ERR_OK);	SAVE_ERRNO
#define SET_ERR_OK	SET_ERR_TYPE(ERR_OK);	NULL_ERRNO

/* help init and zeroed */
#define INIT_ERR 	struct s_err *err = malloc(sizeof(*err)); \
			if (err == NULL) { \
				errno = ENOMEM; \
				perror("INIT_ERR"); \
				exit(ENOMEM); \
			} \
			memset(err, 0, sizeof(*err))
#define FREE_ERR	free(err)

/* help macroses check ERR_CRIT and ERR */
#define IS_CRIT		(err->err == ERR_CRIT)
#define IS_ERR		(err->err == ERR)
#define IS_OK		(err->err == ERR_OK)

#define ERRNO 		err->Errno

/* macros perror and exit if ERR_CRIT, else if ERR - your handle {...} */
#define IFCRIEXI_ELSERR \
	if (IS_CRIT) { \
		errno = ERRNO; \
		FREE_ERR; \
		perror("Err is crit, exit"); \
		exit(errno); \
	} else if (IS_ERR)

#define IFERREXI \
	do { \
	if (IS_ERR || IS_CRIT) { \
		errno = ERRNO; \
		FREE_ERR; \
		perror("Err, exit"); \
		exit(errno); \
	} \
	} while (0) \

#define IFOK_ERRNO \
	if (IS_OK && ERRNO)


#endif /* ERR_H_SENTRY */
