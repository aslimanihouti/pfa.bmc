GTKFLAGS = `pkg-config --libs --cflags gtk+-2.0 gtksourceview-2.0`
LDFLAGS = -lSDL_mixer -lSDL
CFLAGS = -Wall -ggdb
CC= gcc

SRCLINUX = $(wildcard *.c)
OBJLINUX = $(SRCLINUX:.c=.o)

LINUX_EXEC = linux_gui

.PHONY:all clean

all:linux_gui

linux_gui:$(OBJLINUX)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(GTKFLAGS) 

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(GTKFLAGS)

clean: 
	rm $(OBJLINUX)