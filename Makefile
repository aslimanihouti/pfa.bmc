SRCPATHLINUX = gui/linux
SRC = (wildcard *.c)
OBJ = (wildcard *.o)
CC = gcc
CFLAGS = -W -Wall $(pkg-config --libs --cflags gtk+-2.0)

.PHONY: all clean

all: linux_gui

linux_gui: $(SRCPATHLINUX)/$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJ)