CC = gcc
INCLUDES = -I/usr/include/X11
LIBS = -L/usr/lib/x86_64-linux-gnu -lX11 -lXtst

default:
	$(CC) -o footware footware.c $(INCLUDES) $(LIBS)
	strip footware

clean:
	rm footware
