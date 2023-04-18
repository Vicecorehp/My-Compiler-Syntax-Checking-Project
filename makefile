CC = g++
CFLAGS = -I .
DEPS = Syntax.h Word_info.h
OBJ = main.o Syntax.o 
TARGET = target

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o $(TARGET)


