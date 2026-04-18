CFLAGS := -Wall -Wextra -Werror -pedantic -g 
SDL_CFLAGS := `sdl2-config --cflags --libs` -lSDL2_image
SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)
TARGET := main

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	g++ $(CFLAGS) $(SOURCES) -o $@ $(SDL_CFLAGS)

clean:
	rm -rf $(TARGET)