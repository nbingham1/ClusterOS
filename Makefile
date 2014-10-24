ASM = nasm
CXX = g++
CC = gcc
LINK = ld
CXXFLAGS = -c -nostdlib -fno-rtti -fno-builtin -fno-exceptions -nostartfiles
SOURCES	:= $(shell find src -name '*.s') $(shell find src -name '*.c') $(shell find src -name '*.cpp')
OBJECTS	:= $(subst .s,.o,$(subst .c,.o,$(subst .cpp,.o,$(subst src/,build/,$(SOURCES)))))
DIRECTORIES := $(sort $(dir $(OBJECTS)))
SEARCH_PATHS =
LDFLAGS	= -T linker.ld
TARGET	= ClusterOS.bin

all: build floppy

$(TARGET): $(OBJECTS)
	$(LINK) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

floppy: $(TARGET)
	cat stage1 stage2 pad $(TARGET) > cluster_floppy.img
	
build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

build/%.o: src/%.c
	$(CC) $(CXXFLAGS) -o $@ $<

build/%.o: src/%.s
	$(ASM) -f elf -o $@ $<
	
build:
	mkdir $(DIRECTORIES)

clean:
	rm -f $(OBJECTS) $(TARGET)
