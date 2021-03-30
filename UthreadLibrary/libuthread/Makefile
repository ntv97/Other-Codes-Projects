# Target library
lib := libuthread.a

CC := gcc
CFLAGS := -Wall -Wextra -Werror

all: $(lib) 

ifneq ($(V),1)
Q = @
V = 0
endif

ifneq ($(D),1)
CFLAGS += -O2
else
CFLAGS += -g
endif

## TODO: Phase 1
$(lib):  queue.o context.o uthread.o sem.o preempt.o
	ar rcs $(lib) queue.o context.o uthread.o sem.o preempt.o

%.o: %.c sem.h 
	@ echo "CC $@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c private.h uthread.h
	@ echo "CC $@"
	 $(Q)$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c private.h
	@ echo "CC $@"
	 $(Q)$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c uthread.h private.h queue.h
	@ echo "CC $@"
	 $(Q)$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c queue.h
	@ echo "CC $@"
	 $(Q)$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(lib) *.o
