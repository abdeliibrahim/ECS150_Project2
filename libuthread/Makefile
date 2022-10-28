# Target library
lib := libuthread.a
CC  := gcc -D_XOPEN_SOURCE
Cflags := -Wall -Werror -g 
tag:= -c -o $@ $<
all: $(lib)


$(lib): queue.o uthread.o sem.o context.o
	ar rcs libuthread.a queue.o uthread.o sem.o context.o


# making queue.o
%.o: %.c %.h
	$(CC) $(Cflags) -c -o $@ $<

# Making uthread.o
%.o: %.c %.h context.c private.h queue.h
	$(CC) $(Cflags) -c -o $@ $<



# making sem.o
%.o: %.c %.h private.h 
	$(CC) $(Cflags) -c -o $@ $<


clean:
	rm -f  $(lib) libuthread.a queue.o uthread.o sem.o context.o
## TODO: Phase 1
