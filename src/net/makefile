BINARY=$(patsubst %.c,$(ROOT)/bin/%.o,$(wildcard *.c))

all:$(BINARY)

$(ROOT)/bin/%.o:%.c
	@$(CC) -c -l pthread  $< -o $@ -g -I$(ROOT) -O2 -Wall -lpthread



#$(INCLUDE) $(CFLAGS)

