CC := gcc-6
CFLAGS := -g -Ofast -std=c11
WFLAGS := -Wall -Werror -Wextra -Wpedantic -Wfatal-errors
FFLAGS := -floop-optimize -funroll-loops

AR := libtool -static

OBJD := obj
TEST := test
OBJS := $(OBJD)/bits.o 				\
		$(OBJD)/print.o 			\
		$(OBJD)/random.o 			\
		$(OBJD)/timer.o 			\
		$(OBJD)/random.o 			\
		$(OBJD)/test_expect.o 		\
		$(OBJD)/test_funcs.o 		\
		$(OBJD)/test_suite.o
HEAD := inc/extint.h 				\
		inc/template.h

.PRECIOUS: $(OBJD)/%.o

all: lib $(TEST)

run: $(TEST)
	@echo ""
	./$(TEST)

lib: $(OBJD)/bits.o
	$(AR) -o libbits.a $<

$(TEST): $(OBJD)/$(TEST).o $(OBJS)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -o $@ $^

$(OBJD)/$(TEST).o: $(TEST).c $(HEAD)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

$(OBJD)/%.o: %.c %.h $(HEAD)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

$(OBJD)/%.o: util/%.c $(HEAD)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

$(OBJD)/%.o: bittest/%.c bittest/%.h $(HEAD)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

clean:
	/bin/rm -rf *~ $(OBJD)/* $(TEST) libbits.a *.dSYM
