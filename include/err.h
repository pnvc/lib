#ifndef ERR_H_SENTRY
#define ERR_H_SENTRY

/* x32 bit system */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	ERR_OK = 0,
	ERR,
	ERR_CRIT
} e_err;

struct s_err {
	int Errno;
	e_err err;
	int reserved;
};

#define SAVE_ERRNO() err->Errno = errno

/* this means that exit() anyway */
static inline void set_err_crit(struct s_err *err)
{ SAVE_ERRNO(); err->err = ERR_CRIT; }

static inline void set_err_(struct s_err *err)
{ SAVE_ERRNO(); err->err = ERR; 	}

static inline void set_err_ok(struct s_err *err)
{ err->Errno = 0; err->err = ERR_OK; }

#undef SAVE_ERRNO

/* runtime init/free functions for struct s_err */
#define INIT_ERR() struct s_err *err = malloc(sizeof(struct s_err)); \
			if (!err) \
				exit(ENOMEM); \
			memset(err, 0, sizeof(struct s_err));
#define FREE_ERR() free(err);

/* help macroses that will set struct err (SSE) */
#define SET_CRIT()	set_err_crit(err)
#define SET_ERR()	set_err_(err)
#define SET_OK()	set_err_ok(err)

/* help macroses check crit or some error */
#define IS_CRIT()	(err->err == ERR_CRIT)
#define IS_ERR()	(err->err == ERR)
//#define IS_ERR_NERRNO()	(err->err == ERR && !err->Errno);
#define IS_OK()		(err->err == ERR_OK)

#define S_ERR struct s_err *err

#define IFCRIT_EXIT_ELSERR() if (IS_CRIT()) { \
	exit(err->Errno); \
	} else if (IS_ERR())


#endif
