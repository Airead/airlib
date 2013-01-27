CC = gcc
AR = ar

CFLAGS	= -Wall -g
#CFLAGS += -D_AIR_DEBUG
#CFLAGS += $(shell pkg-config --cflags glib-2.0 )

LDFLAGS	= 
#LDFLAGS += $(shell pkg-config --libs glib-2.0)
#LDFLAGS += -lcmockery

INCLUDE = 
INCLUDE += -I../include

OBJ = list.o air_config.o air_log.o air_timer.o

LIB = libair.a

%.o: %.c
	@echo CC -c $< -o $@
	@$(CC) -c $< $(CFLAGS) $(INCLUDE) -o $@ $(LDFLAGS)

$(LIB): $(OBJ)
	@echo AR $^ -o $@ 
	@$(AR) crv $@ $^

.PHONY: clean all test

all: $(LIB)

clean:
	rm -f *~ *.file *.out *.o $(LIB) core.* 
test:
	@echo LIB = $(LIB)
