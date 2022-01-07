CC = gcc
CFLAGS = -Wall -lm -pg -I/usr/include/ -I.
LDFLAGS = -lncurses
DEPS = conway_functions.h visualization_tools.h global_variables.h common_variable_type.h
OBJ = main.o conway_functions.o visualization_tools.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	gcc  -o $@ $^  $(LDFLAGS) $(CFLAGS)

clean:
	rm -f $(OBJ) main
