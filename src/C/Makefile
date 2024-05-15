CC = gcc
LINK = ld
CFLAGS = -g
OBJECTS = test-kvs.o kstore.o config.o
SLIBS = 
PROGRAM = test

$(PROGRAM): 		$(OBJECTS) 
	$(LINK.c) -o $@ $(OBJECTS) $(SLIBS)


config.o:	config.h config.c

kstore.o:	config.h kstore.h kstore.c

test-kvs.o:	config.h kstore.h test-kvs.c
