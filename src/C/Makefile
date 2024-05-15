# not finished...
CC = gcc
LINK = ld
CFLAGS = -g
OBJECTS = config.o set.o connector.o set2.o
SLIBS = 
PROGRAM = test

$(PROGRAM): 		$(OBJECTS) 
	$(LINK.c) -o $@ $(OBJECTS) $(SLIBS)


config.o:	config.h config.c

set.o:		config.h set.h set.c

connector.o:	config.h set.h set2.h connector.h connector.c

set2.o:		config.h set.h connector.h set2.h set2.c
