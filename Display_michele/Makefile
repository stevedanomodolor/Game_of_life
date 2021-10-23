CC = gcc
CFLAGS = -Wall -I/usr/include/ -I.
LDFLAGS = -lncurses 
DEPS = Display.h
OBJ = Display.o ncurses-menu.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

display: $(OBJ)
	gcc  -o $@ $^  $(LDFLAGS) $(CFLAGS)

clean:
	rm -f $(OBJ) display
