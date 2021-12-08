TARGET := ./dlx
BUILD := ./build
SOURCES := ./src
OUTPUT := $(TARGET)

CFILES := $(wildcard $(SOURCES)/*.cpp)
OFILES := $(CFILES:$(SOURCES)/%.cpp=$(BUILD)/%.o)
IDIR := include
CFLAGS += -I $(IDIR)

CC := g++

.PHONY: all clean

all: $(BUILD) $(OUTPUT)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@

clean:
	rm -rf $(BUILD) $(TARGET)

$(BUILD)/%.o: $(SOURCES)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT): $(OFILES)
	$(CC) -o $@ $^

run: $(OUTPUT)
	./$< boards.txt
