CXX = clang++
LD = g++
FLAGS = -Wall -pedantic -g -fsanitize=address,leak -Wno-long-long

SRC_PATH = src
OUTPUT_PATH = hayeuyur
PROGRAM_NAME = downloader

SRC = $(SRC_PATH)/%.cpp
OUTPUT = $(OUTPUT_PATH)/%.o
PROGRAM_PATH = $(OUTPUT_PATH)/$(PROGRAM_NAME)


MODULES = main.o

all: compile

compile: $(OUTPUT_PATH)/$(MODULES)
	$(CXX) $(FLAGS) -o $(PROGRAM_PATH) $^

run: compile
	ASAN_OPTIONS=detect_leaks=1  ./$(PROGRAM_PATH)

debug: compile
	gdb ./$(PROGRAM_PATH)

gen_ycm:
	compiledb make

clean:
	rm -f $(PROGRAM_PATH) $(OUTPUT_PATH)/$(MODULES)

$(OUTPUT) : $(SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

