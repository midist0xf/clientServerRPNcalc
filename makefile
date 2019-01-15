CC=gcc
CFLAGS= -I.
DEPS= stack.h rpn.h
OBJ = stack.o rpn.o server.o

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ) 
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm *.o

