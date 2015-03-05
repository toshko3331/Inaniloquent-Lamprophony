BUILD_DIR = build/
CXX = g++ 
OUT = $(BUILD_DIR)Game
CFLAGS = -std=c++11 -g -Wall

#Directory to source files
SRC = $(shell pwd)/src/
H = $(SRC)Window.h
CPP = $(SRC)Main.cpp $(SRC)Window.cpp 

#Directory to include
INCLUDE = $(CFLAGS) $(shell sdl2-config --cflags)
#Linking Directories
LDFLAGS = $(shell sdl2-config --libs) -lGLEW -lGL 

OBJECTS = $(BUILD_DIR)Main.o $(BUILD_DIR)Window.o

all:$(OUT)
#Linking all the files.	
$(OUT):$(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS) 

#Creating all object files below.
$(BUILD_DIR)Main.o:$(SRC)Main.cpp
	$(CXX) -c $(SRC)Main.cpp $(INCLUDE) -o $(BUILD_DIR)Main.o 

$(BUILD_DIR)Window.o:$(SRC)Window.cpp $(SRC)Window.h
	$(CXX) -c $(SRC)Window.cpp $(INCLUDE) -o $(BUILD_DIR)Window.o 

#All of the clean up stuff below
clean:
	rm -f $(OUT) $(OBJECTS)
clean_obj:
	rm -f $(OBJECTS)
