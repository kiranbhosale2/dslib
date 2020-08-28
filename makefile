CC = gcc
LIBS = rbtree
INC = rbtree 
TESTS = tests
src = $(wildcard rbtree/*.c) 
src = $(wildcard rbtree/*.c) 
src += $(wildcard tests/*.c)
obj = $(src:.c=.o) 	
dep = $(obj:.o=.d)
CFLAGS := -Wall -I$(INC)

dslib: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ 
	
.PHONY: clean
clean:
	rm -f $(obj) dslib