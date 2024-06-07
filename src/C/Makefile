CC = gcc
LINK = ld
CFLAGS = -g
OBJECTS = config.o set.o qesa.o connector.o set2.o test-set2.o
SLIBS = 
PROGRAM = set2

$(PROGRAM): 		$(OBJECTS) 
	$(LINK.c) -o $@ $(OBJECTS) $(SLIBS)


config.o:	config.c

set.o:		set.c

qesa.o:		qesa.c

connector.o:	connector.c

set2.o:		set2.c

test-set2.o:	test-set.c
