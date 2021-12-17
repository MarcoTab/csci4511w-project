TARGET := ./dlx
BUILD := ./build
SOURCES := ./src
OUTPUT := $(TARGET)
SYMLINK := ./backtrack

CFILES := $(wildcard $(SOURCES)/*.cpp)
OFILES := $(CFILES:$(SOURCES)/%.cpp=$(BUILD)/%.o)
IDIR := include
CFLAGS += -I $(IDIR)

CC := g++

.PHONY: all clean

all: $(BUILD) $(OUTPUT) $(SYMLINK)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@

clean:
	rm -rf $(BUILD) $(TARGET) $(SYMLINK)

$(BUILD)/%.o: $(SOURCES)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT): $(OFILES)
	$(CC) -o $@ $^

$(SYMLINK): $(OUTPUT)
	ln -s $(OUTPUT) $(SYMLINK)

run: $(OUTPUT)
	./$< boards.txt
