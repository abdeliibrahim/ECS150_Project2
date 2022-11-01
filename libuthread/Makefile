# Target library
lib := libuthread.a
CC  := gcc -D_XOPEN_SOURCE
Cflags := -Wall -Werror -g 
tag:= -c -o $@ $<
all: $(lib)


$(lib): queue.o uthread.o sem.o preempt.o context.o
	ar rcs libuthread.a queue.o uthread.o sem.o preempt.o context.o 


# making queue.o
%.o: %.c %.h
	$(CC) $(Cflags) -c -o $@ $<

# Making uthread.o
%.o: %.c %.h context.c private.h queue.h
	$(CC) $(Cflags) -c -o $@ $<

preempt.o: preempt.c private.h uthread.h context.c
	$(CC) $(Cflags) -c -o $@ $<

# making context.o
%.o: %.c private.h uthread.h
	$(CC) $(Cflags) -c -o $@ $<

# making sem.o
sem.o: sem.c sem.h private.h queue.h
	$(CC) $(Cflags) -c -o $@ $<



clean:
	rm -f  $(lib) libuthread.a queue.o uthread.o sem.o context.o preempt.o
## TODO: Phase 1
