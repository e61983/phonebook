CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

EXEC = phonebook_orig phonebook_opt
all: $(EXEC)

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-D OPT \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt_debug: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) -ggdb3 $(CFLAGS_opt) \
		-D OPT \
		-DIMPL="\"phonebook_opt.h\"" -o phonebook_opt \
		$(SRCS_common) phonebook_opt.c
		size phonebook_opt
		gdb -q -x gdb_script phonebook_opt
run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_orig && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	echo 1 | sudo tee /proc/sys/vm/drop_caches
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_orig
	echo 1 | sudo tee /proc/sys/vm/drop_caches
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt

copy-test: copy_test.c
	$(CC) $(CFLAGS_common) $^ -o $@

copy-test_debug: copy_test.c
	$(CC) $(CFLAGS_common) -ggdb3 copy_test.c -o copy-test
	size copy-test
	gdb -q copy-test

copy-test.txt: copy-test
	./copy-test

output.txt: cache-test calculate
	./calculate

plot: output.txt
	gnuplot scripts/runtime.gp
	eog runtime.png

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
		calculate orig.txt opt.txt output.txt runtime.png \
		copy-test copy-test.txt 
