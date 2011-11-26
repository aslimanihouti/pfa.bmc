SRCLINUX = $(wildcard *.c)#main.c window.c toolbar.c file_selection.c
OBJLINUX = $(SRCLINUX:.c=.o)

CC = gcc
CFLAGS = -W -Wall
GTKFLAGS = $$(pkg-config --libs --cflags gtk+-2.0)

.PHONY:all clean

all:linux_gui

linux_gui:$(OBJLINUX)
	$(CC) $(CFLAGS) $(GTKFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $(GTKFLAGS) -c $< -o $@

clean: 
	rm $(OBJLINUX)