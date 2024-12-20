# to use this Makefile you have to do next steps in parrent directory of project:
# 1. LIBDIR := path to this lib dir
# 2. LIBOBJ := ...$(LIBDIR)/out.o
# 3. LIBFLAGS := LIBname1=1 LIBname2=1 (i.e. set lib you need, e.g. LIBMSG=1)
# 4. ifdef LIBINLINE 	# if you need inline functions
# 			# from this lib instead usual declare/define
# 	compilerFLAGS += -DLIBINLINE
# 	LIBFLAGS := LIBINLINE=1
#    endif
# 5. target $(LIBOBJ): make -C $(LIBDIR) $(LIBFLAGS), and,
# ofcourse, set this target as depend for you execute file
# thats all!

CC ?= gcc
CCFLAGS :=
AR := ar
ARFLAGS := rcs
STATIC_LIB := libout.a

ifdef LIBGETFD
	lib += getfd
endif

ifdef LIBMSG
	lib += msg
endif

ifdef LIBCPFIL
	lib := $(patsubst %getfd,%,$(lib))
	lib := $(patsubst $msg,%,$(lib))
	lib += cpfil getfd msg
endif

ifdef LIBCPDIR
	lib := $(patsubst %getfd,%,$(lib))
	lib := $(patsubst %cpfil,%,$(lib))
	lib := $(patsubst $msg,%,$(lib))
	lib += cpfil getfd cpdir msg
endif

ifdef LIBINLINE
	CCFLAGS := -DLIBINLINE
	lib := $(patsubst %getfd,%,$(lib))
endif
CCFLAGS += -I../include -c -o
export

ifneq ($(lib),)
.PHONY: all make_lib

all: make_lib
	$(AR) $(ARFLAGS) $(STATIC_LIB) $(shell ls */*.o)

make_lib: $(lib)
	@for dir in $^ ; do \
		$(MAKE) -C $$dir ; \
	done
else
all:
	@echo no libs, try make help
endif

.PHONY: clean help names info_MSG info_GETFD info_CPFIL info_CPDIR
clean:
	-$(MAKE) -C msg clean
	-$(MAKE) -C getfd clean
	-$(MAKE) -C cpfil clean
	-$(MAKE) -C cpdir clean
	-rm $(STATIC_LIB)

help:
	@echo clean all: make clean
	@echo make lib: make LIBname=1
	@echo make libs: make LIBname1=1 LIBname2=1
	@printf "make libs with inline (where possible): \
make LIBINLINE=1 LIBname...=1\n"
	@echo check lib names: make names
	@echo info about lib: make info_name

names:
	@echo available lib names: MSG, GETFD, CPFIL, CPDIR

info_MSG:
	@echo lib MSG contains write functions with simple usage:
	@printf "\texample : msg(message, size) == write(1, message, size)\n"
	@printf "\tif size 0, then size will be automatically find up to \0\n"
	@printf "\tif size < 0, then find size up to \0 and start \
write from message+-size\n"
	@printf "\tif size > 0 then write (1, message, size)\n"

info_GETFD:
	@echo "lib GETFD conatins functions to \
get file descriptor (via open() and openat()):"
	@printf "\texample 1: int fd = getfd_w(filename) == \
open(filename, O_WRONLY)\n"
	@printf "\texample 2: int fd = getfd_cwt(filename) == \
open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0664)\n"
	@printf "\ti.e. _c = creat, _t = trunc\n"
	@printf "\t_w = write, _r = read, _a = append\n"
	@printf "\tread include/getfd.h to see available funcs \
(not many, just main)\n"

info_CPFIL:
	@echo "lib CPFIL contains one function - cpfilmmap(dest, src) - \
copy file"

info_CPDIR:
	@echo "lib CPDIR contains one function - cpdirmmap(dest, src) - \
copy dir recursive"
