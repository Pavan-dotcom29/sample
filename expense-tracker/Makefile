CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = expense-tracker
SOURCES = main.cpp storage.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

