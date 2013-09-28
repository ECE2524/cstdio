CC ?= cc
CFLAGS := -Wall -std=c99 -g
PROGNAME := myprog
SRCS := main.c # add more c source files here, separate by spaces

OBJS := $(SRCS:.c=.o)

pedantic: CFLAGS += -Wextra -pedantic -D_XOPEN_SOURCE=700

all: $(PROGNAME)
pedantic: $(PROGNAME)
 
$(PROGNAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

-include $(OBJS:.o=.P)

# compilation and auto-dependancy generation 
# in one step. Works with gcc and clang
# See http://mad-scientist.net/make/autodep.html
%.o: %.c
	$(CC) $(CFLAGS) -MD -c -o $@ $<
	@cp $*.d $*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	    -e '/^$$/ d' -e 's/$$/ :/' < $*.d >>$*.P; \
	rm -f $*.d

.PHONY: clean
clean:
	rm -f *.o *.P $(PROGNAME)
