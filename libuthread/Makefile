# Target library
lib := libuthread.a
CC  := gcc
Cflags := -Wall -Werror -g 
all: $(lib)

$(lib): queue.o 
	ar rcs libuthread.a queue.o

%.o: %.c %.h
	$(CC) $(Cflags) -c $<


clean:
	rm -f  $(lib) queue.o libuthread.a
## TODO: Phase 1
