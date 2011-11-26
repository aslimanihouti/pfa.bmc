CC = gcc
CFLAGS = -W -Wall
GTKFLAGS = $$(pkg-config --libs --cflags gtk+-2.0)

SRCLINUX = $(wildcard *.c)
OBJLINUX = $(SRCLINUX:.c=.o)

LINUX_EXEC = linux_gui

.PHONY:all clean

all:linux_gui

linux_gui:$(OBJLINUX)
	$(CC) $(CFLAGS) $(GTKFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $(GTKFLAGS) -c $< -o $@

clean: 
	rm $(OBJLINUX)