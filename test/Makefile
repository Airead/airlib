CC = gcc

CFLAGS	= -Wall -g
#CFLAGS += -D_DEBUG_COLOR
#CFLAGS += $(shell pkg-config --cflags glib-2.0 )

LDFLAGS	= 
#LDFLAGS += $(shell pkg-config --libs glib-2.0)
#LDFLAGS += -lcmockery

INCLUDE = 
INCLUDE += -I../include

BIN = test_list.out test_air_config.out test_air_log.out
LIB = ../src/libair.a

%.o: %.c
	@echo CC -c $< -o $@
	@$(CC) -c $< $(CFLAGS) $(INCLUDE) -o $@ $(LDFLAGS)

%.out: %.o ../src/libair.a
	@echo CC $^ -o $@ 
	@$(CC) $^ -o $@ $(LDFLAGS) $(INCLUDE)

.PHONY: clean all test

all: $(LIB) $(BIN)

$(LIB):
	make -C ../src

clean:
	rm -f *~ *.file *.out *.o $(BIN) core.* 
	make clean -C ../src/
test:
	@echo BIN = $(BIN)
