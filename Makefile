TARGET := ./dlx
BUILD := ./build
SOURCES := ./src
OUTPUT := $(TARGET)
BACKTRACK := ./backtrack
HARMONY := ./harmony

CFILES := $(wildcard $(SOURCES)/*.cpp)
OFILES := $(CFILES:$(SOURCES)/%.cpp=$(BUILD)/%.o)
IDIR := include
CFLAGS += -I $(IDIR) -O3 -funroll-loops

CC := g++

.PHONY: all clean

all: $(BUILD) $(OUTPUT) $(BACKTRACK) $(HARMONY)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@

clean:
	rm -rf $(BUILD) $(TARGET) $(BACKTRACK) $(HARMONY)

$(BUILD)/%.o: $(SOURCES)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT): $(OFILES)
	$(CC) -o $@ $^

$(BACKTRACK): $(OUTPUT)
	ln -s $(OUTPUT) $(BACKTRACK)

$(HARMONY): $(OUTPUT)
	ln -s $(OUTPUT) $(HARMONY)

run: $(OUTPUT)
	./$< boards.txt

testbacktrack: ./backtrack
	./backtrack ./input/random-small

testdlx: ./dlx
	./dlx ./input/random-small

testharm: ./harmony
	./harmony ./input/random-small
