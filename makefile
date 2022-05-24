CC = gcc
QUEUE = queue 
RRBTREE = rbtree 
INC += rbtree 
TESTS = tests
src = $(wildcard queue/*.c) 
src += $(wildcard bstree/*.c) 
src += $(wildcard rbtree/*.c) 
src += $(wildcard tests/*.c)
obj = $(src:.c=.o) 	
dep = $(obj:.o=.d)
CFLAGS := -Wall -I$(QUEUE) -I$(RRBTREE)

dslib: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ 
	
.PHONY: clean
clean:
	rm -f $(obj)