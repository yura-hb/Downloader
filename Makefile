.PHONY: doc

CXX = clang++
LD = g++
FLAGS = -std=c++14 -Wall -pedantic -g -fsanitize=address -Wno-long-long $(INCLUDE_FLAGS)
INCLUDE_FLAGS = -I/usr/local/Cellar/libpng/1.6.37/include

SRC_PATH = src
OUTPUT_PATH = hayeuyur
PROGRAM_NAME = downloader.o

SRC = $(SRC_PATH)/%.cpp
NETWORKING_SRC = $(SRC_PATH)/Networking/%.cpp
NETWORKING_HELPERS_SRC = $(SRC_PATH)/Networking/Helpers/%.cpp
TEMPLATES_SRC = $(SRC_PATH)/Templates/%.cpp
DOWNLOADER_SRC = $(SRC_PATH)/Downloader/%.cpp
FILE_MANAGER_SRC = $(SRC_PATH)/FileManager/%.cpp
FILE_MANAGER_MODELS_SRC = $(SRC_PATH)/FileManager/Models/%.cpp
SYNTAX_ANALYZER_SRC = $(SRC_PATH)/SyntaxAnalyzer/%.cpp
SYNTAX_ANALYZER_MODELS_SRC = $(SRC_PATH)/SyntaxAnalyzer/Models/%.cpp

OUTPUT = $(OUTPUT_PATH)/%.o
PROGRAM_PATH = $(OUTPUT_PATH)/$(PROGRAM_NAME)
DOC_PATH = doc
DOXYGEN_FILE = doxygex.dox

MODULES = $(OUTPUT_PATH)/main.o $(OUTPUT_PATH)/Data.o $(OUTPUT_PATH)/Exception.o $(OUTPUT_PATH)/Socket.o \
		$(OUTPUT_PATH)/HTTPClient.o \
	  $(OUTPUT_PATH)/Receiver.o $(OUTPUT_PATH)/Request.o $(OUTPUT_PATH)/URL.o \
	  $(OUTPUT_PATH)/Header.o $(OUTPUT_PATH)/RequestMethod.o $(OUTPUT_PATH)/Version.o \
		$(OUTPUT_PATH)/ChunkMerger.o \
	  $(OUTPUT_PATH)/Response.o $(OUTPUT_PATH)/StringConvertible.o $(OUTPUT_PATH)/ResponseStatus.o \
		$(OUTPUT_PATH)/Reference.o 	$(OUTPUT_PATH)/LocalReference.o $(OUTPUT_PATH)/RemoteReference.o \
		$(OUTPUT_PATH)/ReferenceConverter.o $(OUTPUT_PATH)/AbstractPattern.o $(OUTPUT_PATH)/Attribute.o \
		$(OUTPUT_PATH)/Comment.o $(OUTPUT_PATH)/Analyzer.o $(OUTPUT_PATH)/CSSAnalyzer.o \
		$(OUTPUT_PATH)/HTMLAnalyzer.o $(OUTPUT_PATH)/PageDownloader.o  $(OUTPUT_PATH)/FileManager.o

all: compile

compile: $(MODULES)
	$(CXX) $(FLAGS) -o $(PROGRAM_PATH) $^

run: compile
	./$(PROGRAM_PATH) 2>&1

debug: compile
	gdb ./$(PROGRAM_PATH)

doc:
	doxygen $(DOXYGEN_FILE)

gen_ycm:
	compiledb make

clean:
	rm -rf $(OUTPUT_PATH)/*

$(OUTPUT) : $(SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(NETWORKING_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(NETWORKING_HELPERS_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(TEMPLATES_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(DOWNLOADER_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(FILE_MANAGER_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(FILE_MANAGER_MODELS_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(SYNTAX_ANALYZER_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(SYNTAX_ANALYZER_MODELS_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@
