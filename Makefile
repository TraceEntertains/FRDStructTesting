CXX = g++
CXXFLAGS = -std=c++20 -Wall
LDFLAGS = -lboost_serialization
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = test.x86_64

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)
