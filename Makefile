CC = gcc

CFLAGS = -Wall -g

LDLIBS = -lcrypto 

TARGET = main
SRCS = main.c md5.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS) 


clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean