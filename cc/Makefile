CC := g++-6
CFLAGS := -g -Ofast -std=c++14
WFLAGS := -Wall -Werror -Wextra -Wpedantic -Wfatal-errors
FFLAGS := -floop-optimize -funroll-loops

# AR := libtool -static

OBJD := obj
TEST := test
OBJS := $(OBJD)/bits.o              \
		$(OBJD)/serial.o 			\
		$(OBJD)/Random.o 			\
		$(OBJD)/TestCases.o 		\
		$(OBJD)/uint256_t.o
HEAD := inc/extint.hh

.PRECIOUS: $(OBJD)/%.o

all: $(TEST)

run: $(TEST)
	@echo ""
	./$(TEST)

# lib: $(OBJD)/bitc.o
# 	$(AR) -o libbits.a $<

$(TEST): $(OBJD)/$(TEST).o $(OBJS)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -o $@ $^

$(OBJD)/$(TEST).o: $(TEST).cc $(HEAD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

$(OBJD)/%.o: %.cc %.hh $(HEAD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

$(OBJD)/%.o: util/%.cc util/%.hh $(HEAD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

$(OBJD)/%.o: testing/%.cc testing/%.hh $(HEAD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

$(OBJD)/%.o: ext/%.cc ext/%.hh $(HEAD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(WFLAGS) $(FFLAGS) -c -o $@ $<

clean:
	/bin/rm -rf *~ $(OBJD) $(TEST) *.dSYM .DS_Store
