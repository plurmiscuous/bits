CC := gcc-6
CFLAGS := -g -Ofast -std=c11
WFLAGS := -Wall -Werror -Wextra -Wpedantic -Wfatal-errors
FFLAGS := -floop-optimize -funroll-loops

OBJD := obj
OBJS := $(OBJD)/bits.o              \
		$(OBJD)/print.o             \
		$(OBJD)/random.o            \
		$(OBJD)/timer.o             \
		$(OBJD)/random.o            \
		$(OBJD)/test_serial.o       \
		$(OBJD)/test_suite.o
HEAD := inc/extint.h                \
		inc/N.h

.PRECIOUS: $(OBJD)/%.o

all: test

run: test
	@echo ""
	./test

test: $(OBJD)/test.o $(OBJS)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -o $@ $^

$(OBJD)/test.o: testing/test.c $(HEAD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

$(OBJD)/%.o: %.c %.h $(HEAD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

$(OBJD)/%.o: util/%.c util/%.h $(HEAD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

$(OBJD)/%.o: testing/%.c testing/%.h $(HEAD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

clean:
	/bin/rm -rf *~ $(OBJD) test log.txt *.dSYM .DS_Store
