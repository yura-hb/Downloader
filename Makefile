.PHONY: doc

LD = ASAN_OPTIONS=detect_leaks=1 clang++
CXX = g++
FLAGS = -std=c++14 -Wall -pedantic -g -fsanitize=address -Wno-long-long

SRC_PATH = src
OUTPUT_PATH = hayeuyur
PROGRAM_NAME = downloader.o

SRC = $(SRC_PATH)/%.cpp
NETWORKING_SRC = $(SRC_PATH)/Networking/%.cpp
BASE_SRC = $(SRC_PATH)/Base/%.cpp
FILE_MANAGER_SRC = $(SRC_PATH)/FileManager/%.cpp
FILE_MANAGER_MODELS_SRC = $(SRC_PATH)/FileManager/Models/%.cpp
SYNTAX_ANALYZER_SRC = $(SRC_PATH)/SyntaxAnalyzer/%.cpp
SYNTAX_ANALYZER_MODELS_SRC = $(SRC_PATH)/SyntaxAnalyzer/Models/%.cpp
DOWNLOADER_SRC = $(SRC_PATH)/Downloader/%.cpp
DOWNLOADER_HELPERS_SRC = $(SRC_PATH)/Downloader/Helpers/%.cpp

OUTPUT = $(OUTPUT_PATH)/%.o
PROGRAM_PATH = $(OUTPUT_PATH)/$(PROGRAM_NAME)
DOC_PATH = doc
DOXYGEN_FILE = doxygex.dox

MODULES = $(OUTPUT_PATH)/main.o \
    \
    $(OUTPUT_PATH)/Data.o $(OUTPUT_PATH)/Exception.o $(OUTPUT_PATH)/Logger.o \
    \
		$(OUTPUT_PATH)/Socket.o $(OUTPUT_PATH)/HTTPClient.o \
	  $(OUTPUT_PATH)/Receiver.o $(OUTPUT_PATH)/Request.o $(OUTPUT_PATH)/URL.o \
	  $(OUTPUT_PATH)/Header.o $(OUTPUT_PATH)/RequestMethod.o $(OUTPUT_PATH)/Version.o \
	  $(OUTPUT_PATH)/Response.o  $(OUTPUT_PATH)/ResponseStatus.o \
		\
		$(OUTPUT_PATH)/Reference.o $(OUTPUT_PATH)/LocalReference.o $(OUTPUT_PATH)/RemoteReference.o \
		$(OUTPUT_PATH)/FileManager.o \
		\
	  $(OUTPUT_PATH)/AbstractPattern.o $(OUTPUT_PATH)/Attribute.o $(OUTPUT_PATH)/HTMLAttribute.o \
		$(OUTPUT_PATH)/Comment.o $(OUTPUT_PATH)/BeginEndAttribute.o \
		$(OUTPUT_PATH)/Analyzer.o $(OUTPUT_PATH)/CSSAnalyzer.o \
		$(OUTPUT_PATH)/HTMLAnalyzer.o \
		\
		$(OUTPUT_PATH)/DownloadFileTree.o \
    \
		$(OUTPUT_PATH)/ChunkMerger.o $(OUTPUT_PATH)/ResponseSaveManager.o $(OUTPUT_PATH)/ReferenceConverter.o\
		$(OUTPUT_PATH)/FileDownloader.o $(OUTPUT_PATH)/PageMirror.o

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

$(OUTPUT) : $(BASE_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(DOWNLOADER_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(DOWNLOADER_HELPERS_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(FILE_MANAGER_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(FILE_MANAGER_MODELS_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(SYNTAX_ANALYZER_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@

$(OUTPUT) : $(SYNTAX_ANALYZER_MODELS_SRC)
	$(CXX) $(FLAGS) -c $^ -o $@
