CC = gcc
INCLUDES = -I/usr/X11R6/include
LIBS = -L/usr/X11R6/lib -lX11 -lXtst

default: 
	$(CC) $(INCLUDES) $(LIBS) -o footware footware.c
	strip footware

clean:
	rm footware
