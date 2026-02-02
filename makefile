CC = clang
CFLAGS = -std=c11 -O3 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit

# Find all .c files recursively
SRCS = $(shell find . -name "*.c")
OBJS = $(SRCS:.c=.o)
TARGET = app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile .c → .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

clear:
	rm -f $(OBJS) $(TARGET)
