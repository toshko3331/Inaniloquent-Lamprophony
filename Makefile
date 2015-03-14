BUILD_DIR = build/
CXX = g++ 
OUT = $(BUILD_DIR)Game
CFLAGS = -std=c++11 -g -Wall

#Directory to source files
SRC = $(shell pwd)/src/
H = $(SRC)Window.h $(SRC)Shader.h $(SRC)Vertex.h $(SRC)GameObject.h $(SRC)OBJLevelLoader.h $(SRC)Bitmap.h $(SRC)Textures.h $(SRC)Camera.h
CPP = $(SRC)Main.cpp $(SRC)Window.cpp $(SRC)Shader.cpp $(SRC)Vertex.cpp $(SRC)GameObject.cpp $(SRC)OBJLevelLoader.cpp $(SRC)Bitmap.cpp $(SRC)Textures.cpp $(SRC)Camera.cpp

#Directory to include
INCLUDE = $(CFLAGS) $(shell sdl2-config --cflags) -lpng16
#Linking Directories
LDFLAGS = $(shell sdl2-config --libs) -lGLEW -lGL -lpng16

OBJECTS = $(BUILD_DIR)Main.o $(BUILD_DIR)Window.o $(BUILD_DIR)Shader.o $(BUILD_DIR)Vertex.o $(BUILD_DIR)GameObject.o $(BUILD_DIR)OBJLevelLoader.o $(BUILD_DIR)Bitmap.o $(BUILD_DIR)Textures.o $(BUILD_DIR)Camera.o

all:$(OUT)
#Linking all the files.	
$(OUT):$(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS) 

#Creating all object files below.
$(BUILD_DIR)Main.o:$(SRC)Main.cpp
	$(CXX) -c $(SRC)Main.cpp $(INCLUDE) -o $(BUILD_DIR)Main.o 

$(BUILD_DIR)Window.o:$(SRC)Window.cpp $(SRC)Window.h
	$(CXX) -c $(SRC)Window.cpp $(INCLUDE) -o $(BUILD_DIR)Window.o 

$(BUILD_DIR)Shader.o:$(SRC)Shader.cpp $(SRC)Shader.h
	$(CXX) -c $(SRC)Shader.cpp $(INCLUDE) -o $(BUILD_DIR)Shader.o 

$(BUILD_DIR)Vertex.o:$(SRC)Vertex.cpp $(SRC)Vertex.h
	$(CXX) -c $(SRC)Vertex.cpp $(INCLUDE) -o $(BUILD_DIR)Vertex.o 

$(BUILD_DIR)GameObject.o:$(SRC)GameObject.cpp $(SRC)GameObject.h
	$(CXX) -c $(SRC)GameObject.cpp $(INCLUDE) -o $(BUILD_DIR)GameObject.o 

$(BUILD_DIR)OBJLevelLoader.o:$(SRC)OBJLevelLoader.cpp $(SRC)OBJLevelLoader.h
	$(CXX) -c $(SRC)OBJLevelLoader.cpp $(INCLUDE) -o $(BUILD_DIR)OBJLevelLoader.o 

$(BUILD_DIR)Bitmap.o:$(SRC)Bitmap.cpp $(SRC)Bitmap.h
	$(CXX) -c $(SRC)Bitmap.cpp $(INCLUDE) -o $(BUILD_DIR)Bitmap.o 

$(BUILD_DIR)Textures.o:$(SRC)Textures.cpp $(SRC)Textures.h
	$(CXX) -c $(SRC)Textures.cpp $(INCLUDE) -o $(BUILD_DIR)Textures.o 

$(BUILD_DIR)Camera.o:$(SRC)Camera.cpp $(SRC)Camera.h
	$(CXX) -c $(SRC)Camera.cpp $(INCLUDE) -o $(BUILD_DIR)Camera.o 

#All of the clean up stuff below
clean:
	rm -f $(OUT) $(OBJECTS)
clean_obj:
	rm -f $(OBJECTS)
