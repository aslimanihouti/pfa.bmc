export CC  = gcc
export CFLAGS = -W -Wall

LINUX_GUI_DIR = gui/linux

LINUX_EXEC = $(LINUX_GUI_DIR)/linux_gui

.PHONY: all clean

all: $(LINUX_EXEC)

$(LINUX_EXEC):
	@(cd $(LINUX_GUI_DIR) && $(MAKE) && cp linux_gui ../../)

clean: 
	@(cd $(LINUX_GUI_DIR) && $(MAKE) $@)