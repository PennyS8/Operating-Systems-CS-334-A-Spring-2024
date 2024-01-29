CC=gcc
CFLAGS=-Wall

# Target executable
TARGET=driver

# Source files
SRCS=driver.c resize.c

# Object files
OBJS=$(SRCS:.c=.o)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(TARGET) $(OBJS)
