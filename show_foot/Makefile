TARGET = showfoot
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Show Foot
# PSP_EBOOT_ICON = icon.png

PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)

LIBS = -lm -lfreetype -lSDL_image -lpng -ljpeg -lz -lSDL_ttf -lSDL_gfx $(shell $(PSPDIR)/bin/sdl-config --libs)

include $(PSPSDK)/lib/build.mak
