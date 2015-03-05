#all: hello-cpp-world hello-c-world
all: help
.PNONY: all clean

CFLAGS=-Wall -lm -O2 -pipe -ansi

%: %.cc
	g++ -std=c++11 $< -o $@

%: %.c
	@echo "==> Compiling.."
	gcc $(CFLAGS) $< -o $@
	@echo "==> Running.."
	./$@ < $@.in > $@.res
	@echo "==> Checking result.."
	diff -s -Z $@.out $@.res

help:
	@echo "Call make <problem number>"
	@echo "Ex.: make 100"

SRCS = $(wildcard *.c)
BINS = $(SRCS:%.c=%)

clean:
	@rm -v -f $(BINS)