# Target library
lib := libfs.a

objs    := fs.o disk.o

CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -MMD
CFLAGS  += -g

ifneq ($(V),1)
Q = @
endif

all: $(lib)

deps := $(patsubst %.o,%.d,$(objs))
-include $(deps)

$(lib): $(objs)
	@echo "CC $@"
	ar rcs $(lib) $(objs)

%.o: %.c
	@echo "CC $@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "clean"
	$(Q)rm -f $(targets) $(objs) $(deps)

## TODO: Phase 1
