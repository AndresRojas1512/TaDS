.PHONY : clean func unit release debug
CC := gcc
CFLAGS := -std=c99 -pedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion 
DFLAGS := -g3 --coverage

# Uncomment this line to enable time measurement mode (disabling prints)
TM_FLAG := -DTM

INC := inc
OUT := out
SRC := src

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c,$(OUT)/%.o, $(SRCS))

APP_EXE := app.exe

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
	$(CC) $(CFLAGS) $(TM_FLAG) $(OBJS) -o $@

$(OUT)/%.o: $(SRC)/%.c 
	$(CC) $(CFLAGS) $(TM_FLAG) -I$(INC) -c $< -o $@

$(OUT):
	mkdir -p $@

clean:
	rm -f -r $(OUT) debug.lastbuildstate release.lastbuildstate *.gcov *.exe
