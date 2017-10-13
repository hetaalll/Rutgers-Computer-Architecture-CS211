CC = gcc
CCFLAGS = -g -Wall -std=c99 -lm -I.
RM = rm -f
MYSTERY = mystery

all: $(MYSTERY)

$(MYSTERY): mystery.c
	$(CC) $(CCFLAGS) -o mystery mystery.c

clean:
	$(RM) $(MYSTERY)
