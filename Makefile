all:
	gcc -g -Og `pkg-config --cflags sdl2` glyph.c `pkg-config --libs sdl2`
