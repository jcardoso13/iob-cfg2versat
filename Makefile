# the compiler: gcc for C program, define as g++ for C++
CC=gcc
ALIB=./libdarknet.a
SLIB=
OBJDIR=../darknet/obj/
COMMON= -Iinclude/ -Isrc/
CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC
LDFLAGS= -lm -pthread 

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS=-g -Wall
# the build target executable:
TARGET=iob-cfg2versat
all: $(TARGET) $(OBJDIR)
$(TARGET):app.c parse2compiler.c write2yolo.c iob-cfg2versat.h $(ALIB)
	$(CC) $(CFLAGS) -o iob-cfg2versat app.c parse2compiler.c write2yolo.c $(ALIB) $(LDFLAGS)

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET)

