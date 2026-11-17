CC ?= cc
PKG_CONFIG ?= pkg-config
CFLAGS ?= -O2
CFLAGS += -std=c11 -Wall -Wextra -Wpedantic

SDL_PACKAGES = sdl2 SDL2_image SDL2_ttf
SDL_SDK = .date-simulator-sdk
ifneq ($(wildcard $(SDL_SDK)/include/SDL2/SDL.h),)
SDL_CFLAGS = -I$(SDL_SDK)/include
SDL_LIBS = -L$(SDL_SDK)/lib -Wl,-rpath,'$$ORIGIN/$(SDL_SDK)/lib' -l:libSDL2_image-2.0.so.0 -l:libSDL2_ttf-2.0.so.0 -l:libSDL2-2.0.so.0
else
SDL_CFLAGS = $(shell $(PKG_CONFIG) --cflags $(SDL_PACKAGES))
SDL_LIBS = $(shell $(PKG_CONFIG) --libs $(SDL_PACKAGES))
endif

INTERFACE = Code/Choix.c Code/interface.c
INTERFACE_H = Code/Choix.h Code/interface.h

.PHONY: all clean

all: date-simulator

date-simulator: Code/main_graphique.c Code/jeu.c Code/jeu.h $(INTERFACE) $(INTERFACE_H)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SDL_CFLAGS) $(LDFLAGS) Code/main_graphique.c Code/jeu.c $(INTERFACE) $(SDL_LIBS) $(LDLIBS) -o $@

jeu-terminal: Code/main.c Code/jeu.c Code/jeu.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) Code/main.c Code/jeu.c $(LDLIBS) -o $@

test-interface: Code/test_interface.c $(INTERFACE) $(INTERFACE_H)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SDL_CFLAGS) $(LDFLAGS) Code/test_interface.c $(INTERFACE) $(SDL_LIBS) $(LDLIBS) -o $@

clean:
	rm -f date-simulator jeu-terminal test-interface
