.PHONY: doc


CXX = clang++
LD = g++
FLAGS = -std=c++14 -Wall -pedantic -g -fsanitize=address,leak -Wno-long-long

SRC_PATH = src
OUTPUT_PATH = hayeuyur
PROGRAM_NAME = downloader

SRC = $(SRC_PATH)/%.cpp
OUTPUT = $(OUTPUT_PATH)/%.o
PROGRAM_PATH = $(OUTPUT_PATH)/$(PROGRAM_NAME)
DOC_PATH = doc
DOXYGEN_FILE = doxygex.dox

MODULES = $(OUTPUT_PATH)/main.o $(OUTPUT_PATH)/Socket.o $(OUTPUT_PATH)/HTTPClient.o $(OUTPUT_PATH)/Receiver.o $(OUTPUT_PATH)/HTTPRequest.o $(OUTPUT_PATH)/URL.o

all: compile

compile: $(MODULES)
	$(CXX) $(FLAGS) -o $(PROGRAM_PATH) $^

run: compile
	ASAN_OPTIONS=detect_leaks=1  ./$(PROGRAM_PATH)

debug: compile
	gdb ./$(PROGRAM_PATH)

doc:
	doxygen $(DOXYGEN_FILE)

gen_ycm:
	compiledb make

clean:
	rm -f $(PROGRAM_PATH) $(OUTPUT_PATH)/$(MODULES)
	rm -rf $(DOC_PATH)

$(OUTPUT) : $(SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

