.PHONY: doc

CXX = clang++
LD = g++
FLAGS = -std=c++14 -Wall -pedantic -g -fsanitize=address,leak -Wno-long-long

SRC_PATH = src
OUTPUT_PATH = hayeuyur
PROGRAM_NAME = downloader.o

SRC = $(SRC_PATH)/%.cpp
HTML_SRC = $(SRC_PATH)/HTML/%.cpp
HTML_STATES_SRC = $(SRC_PATH)/HTML/States/%.cpp
NETWORKING_SRC = $(SRC_PATH)/Networking/%.cpp
TEMPLATES_SRC = $(SRC_PATH)/Templates/%.cpp

OUTPUT = $(OUTPUT_PATH)/%.o
PROGRAM_PATH = $(OUTPUT_PATH)/$(PROGRAM_NAME)
DOC_PATH = doc
DOXYGEN_FILE = doxygex.dox

MODULES = $(OUTPUT_PATH)/main.o $(OUTPUT_PATH)/Socket.o $(OUTPUT_PATH)/HTTPClient.o \
	  $(OUTPUT_PATH)/Receiver.o $(OUTPUT_PATH)/Request.o $(OUTPUT_PATH)/URL.o \
	  $(OUTPUT_PATH)/Header.o $(OUTPUT_PATH)/RequestMethod.o $(OUTPUT_PATH)/Version.o \
	  $(OUTPUT_PATH)/HTTPParser.o $(OUTPUT_PATH)/StringConvertible.o $(OUTPUT_PATH)/ResponseStatus.o \
		$(OUTPUT_PATH)/HTMLToken.o $(OUTPUT_PATH)/HTMLTokenizerState.o $(OUTPUT_PATH)/HTMLTokenizer.o \
		$(OUTPUT_PATH)/HTMLTokenizerContext.o $(OUTPUT_PATH)/HTMLTagStartState.o

all: compile

compile: $(MODULES)
	$(CXX) $(FLAGS) -o $(PROGRAM_PATH) $^

run: compile
	ASAN_OPTIONS=detect_leaks=1  ./$(PROGRAM_PATH) 2>&1

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

$(OUTPUT) : $(HTML_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(HTML_STATES_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(NETWORKING_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(TEMPLATES_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@
