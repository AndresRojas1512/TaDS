.PHONY : clean func unit release debug
CC := gcc
CFLAGS := -std=c99 -pedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion 
DFLAGS := -g3 --coverage
UTFLAGS := -lcheck

INC := inc
OUT := out
SRC := src
UNIT_TESTS := unit_tests
FUNC := ./func_tests/scripts

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c,$(OUT)/%.o, $(SRCS))
UNITS := $(UNIT_TESTS)/check_mysort.c $(UNIT_TESTS)/check_key.c $(UNIT_TESTS)/check_main.c
UNIT_OBJS := $(patsubst $(UNIT_TESTS)/%.c,$(OUT)/%.o, $(UNITS))
UNIT_OBJS += $(OBJS)
UNIT_LINK_OBJS := $(filter-out $(OUT)/main.o, $(UNIT_OBJS))

APP_EXE := app.exe
UNIT_TESTS_EXE := unit_tests.exe

.NOTPARALLEL: *.lastbuildstate

release: release.lastbuildstate | $(APP_EXE)

debug: CFLAGS += $(DFLAGS)
debug: debug.lastbuildstate | $(APP_EXE)

release.lastbuildstate:
	rm -f *.exe out/* *.lastbuildstate
	touch release.lastbuildstate

debug.lastbuildstate:
	rm -f *.exe out/* *.lastbuildstate
	touch debug.lastbuildstate

$(APP_EXE): $(OUT) | $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(UNIT_TESTS_EXE): CFLAGS += $(DFLAGS)
$(UNIT_TESTS_EXE): $(OUT) | $(UNIT_LINK_OBJS)
	$(CC) $(UNIT_LINK_OBJS) $(UTFLAGS) $(DFLAGS) -o $@ 

$(OUT)/%.o: $(SRC)/%.c 
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(OUT)/%.o: $(UNIT_TESTS)/%.c
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(OUT):
	mkdir -p $@

func: debug
	cd $(FUNC) && ./func_tests.sh

unit: $(UNIT_TESTS_EXE)
	valgrind --leak-check=full ./$(UNIT_TESTS_EXE)
	gcov -f -r $(OUT)/*.gcno

clean:
	rm -f -r $(OUT) debug.lastbuildstate release.lastbuildstate *.gcov *.exe
