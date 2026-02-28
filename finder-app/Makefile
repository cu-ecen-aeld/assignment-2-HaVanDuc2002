CC = $(CROSS_COMPILE)gcc
CFLAGS ?= -g -Wall -Werror
TARGET = writer

all: $(TARGET)

$(TARGET): writer.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) writer.o

writer.o: writer.c
	$(CC) $(CFLAGS) -c writer.c -o writer.o

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
