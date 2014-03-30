TARGET = hello
OBJS = main.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Hello World

PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)

LIBS = -lSDL_ttf -lfreetype -lSDL_image -lpng -ljpeg -lz $(shell $(PSPDIR)/bin/sdl-config --libs)

include $(PSPSDK)/lib/build.mak


# TARGET = SDL_image
# OBJS = main.o
# 
# INCDIR =
# CFLAGS = -G4 -Wall -O3 -I/usr/local/pspdev/psp/include/SDL
# CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
# ASFLAGS = $(CFLAGS)
# 
# 
# PSPSDK=$(shell psp-config --pspsdk-path)
# PSPBIN = $(PSPSDK)/../bin
# 
# LIBDIR =
# LDFLAGS =
# STDLIBS= -lSDLmain -lSDL_image -lSDL -lpng -ljpeg -lm -lz \
# -lpspsdk -lpspctrl -lpsprtc -lpsppower -lpspgu -lpspaudiolib -lpspaudio -lpsphprm
# LIBS=$(STDLIBS)$(YOURLIBS)
# 
# 
# EXTRA_TARGETS = EBOOT.PBP
# PSP_EBOOT_TITLE = Les images
# 
# PSPSDK=$(shell psp-config --pspsdk-path)
# DEFAULT_CFLAGS = $(shell $(SDL_CONFIG) --cflags)
# include $(PSPSDK)/lib/build.mak 