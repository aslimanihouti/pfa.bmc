GTKFLAGS = `pkg-config --libs --cflags gtk+-3.0 gtksourceview-3.0`
LDFLAGS = -lSDL_mixer -lSDL -levview3 -levdocument3
CFLAGS = -Wall -ggdb -I/usr/include/evince/3.0
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