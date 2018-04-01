#authors : Maxime Lordey / Quentin Sibué

CC= gcc
OBJS = image.o PPM.o
CFLAGS = -Wall -D K=8
CPPFLAGS = -I ../the_headers
EXEC = ../bin/traitement_image


all : $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)


clean:
	rm $(OBJS)
