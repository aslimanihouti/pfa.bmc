GTKFLAGS = `pkg-config --libs --cflags gtk+-2.0`
CC= gcc

SRCLINUX = $(wildcard *.c)
OBJLINUX = $(SRCLINUX:.c=.o)

LINUX_EXEC = linux_gui

.PHONY:all clean

all:linux_gui

linux_gui:$(OBJLINUX)
	$(CC) $(CFLAGS) $^ -o $@ $(GTKFLAGS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(GTKFLAGS)

clean: 
	rm $(OBJLINUX)