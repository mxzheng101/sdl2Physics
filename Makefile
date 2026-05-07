CFLAGS := -Wall -Wextra -Werror -pedantic -g 
SDL_CFLAGS := `sdl2-config --cflags --libs` -lSDL2_image
SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)

BOUNCY_SOURCES := $(filter-out PendyWendy.cpp, $(SOURCES))
PENDULUM_SOURCES := $(filter-out bouncyBall.cpp, $(SOURCES))

all: bouncyBall Pendulum

bouncyBall: $(BOUNCY_SOURCES) $(HEADERS)
	g++ $(CFLAGS) $(BOUNCY_SOURCES) -o bouncyBall.o $(SDL_CFLAGS)

Pendulum: $(PENDULUM_SOURCES) $(HEADERS)
	g++ $(CFLAGS) $(PENDULUM_SOURCES) -o pendyWendy.o $(SDL_CFLAGS)

clean:
	rm -rf *.o