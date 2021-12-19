TARGET := ./dlx
BUILD := ./build
SOURCES := ./src
OUTPUT := $(TARGET)
BACKTRACK := ./backtrack
HARMONY := ./harmony
SIMANNEAL := ./simanneal

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
	./backtrack input/random_17 > /dev/null
	./backtrack input/random_18-22 > /dev/null
	./backtrack input/random_23 > /dev/null
	./backtrack input/random_24 > /dev/null
	./backtrack input/random_25 > /dev/null
	./backtrack input/random_26 > /dev/null
	./backtrack input/random_27 > /dev/null
	./backtrack input/random_28 > /dev/null
	./backtrack input/random_easy > /dev/null

testdlx: ./dlx
	./dlx input/random_17 > /dev/null
	./dlx input/random_18-22 > /dev/null
	./dlx input/random_23 > /dev/null
	./dlx input/random_24 > /dev/null
	./dlx input/random_25 > /dev/null
	./dlx input/random_26 > /dev/null
	./dlx input/random_27 > /dev/null
	./dlx input/random_28 > /dev/null
	./dlx input/random_easy > /dev/null

testharm: ./harmony
	./harmony input/random_17 > /dev/null
	./harmony input/random_18-22 > /dev/null
	./harmony input/random_23 > /dev/null
	./harmony input/random_24 > /dev/null
	./harmony input/random_25 > /dev/null
	./harmony input/random_26 > /dev/null
	./harmony input/random_27 > /dev/null
	./harmony input/random_28 > /dev/null
	./harmony input/random_easy > /dev/null

testsimanneal: ./simanneal
	./simanneal input/random_17 > /dev/null
	./simanneal input/random_18-22 > /dev/null
	./simanneal input/random_23 > /dev/null
	./simanneal input/random_24 > /dev/null
	./simanneal input/random_25 > /dev/null
	./simanneal input/random_26 > /dev/null
	./simanneal input/random_27 > /dev/null
	./simanneal input/random_28 > /dev/null
	./simanneal input/random_easy > /dev/null
