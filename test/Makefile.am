AM_CPPFLAGS = -I$(top_srcdir)/include
LDLIB = ../src/libair.a /usr/local/lib/liblcut.a

noinst_PROGRAMS = test_list.out test_air_config.out test_air_log.out test_air_timer.out
test_air_config_out_SOURCE = test_air_config.c
test_air_config_out_LDADD = ../src/libair.a

test_air_log_out_SOURCE = test_air_log.c 
test_air_log_out_LDADD = ../src/libair.a

test_air_timer_out_SOURCE = test_air_timer.c
test_air_timer_out_LDADD = ../src/libair.a

test_list_out_SOURCE = test_list.c
test_list_out_LDADD = ../src/libair.a

noinst_PROGRAMS += test_list_unit
test_list_unit_SOURCE = test_list_unit.c
test_list_unit_LDADD = $(LDLIB)

