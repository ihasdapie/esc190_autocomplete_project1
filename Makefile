# really simple makefile to just compile together all the c files in a directory
# stuff headers in headers/*.h 

# For reference: 
# $? List of prerequisites (files the target depends on) changed more recently than the current target
# $@ Name of the current target
# $< Name of the current prerequisite
# $* Name of the current prerequisite, without any suffix

TARGET=lab.bin

C_SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = ${C_SOURCES:.c=.o }

CC = /usr/bin/gcc
GDB = /usr/bin/gdb
CFLAGS= -g # use debug symbols on gcc

$(info >> C_SOURCES ARE $(C_SOURCES))
$(info >> HEADERS ARE $(HEADERS))
$(info >> OBJECTS ARE $(OBJECTS))

$(TARGET): $(OBJECTS)
	$(info Targets: $(TARGET), Objects: $(OBJECTS))
	$(CC) $(CFLAGS) $(OBJECTS) -Wall -o $@
	@echo "Compilation Complete"


$(OBJECTS): $(C_SOURCES) $(HEADERS)
	$(info $(C_SOURCES), $(HEADERS))
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	$(info CLEANING)
	find . -type f \( -name '*.o' -o -name "*.bin" -o -name "*.dis" -o -name ".out" \) -delete




