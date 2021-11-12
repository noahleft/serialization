
CXXFLAGS = -std=c++11
DATA_SRC = main.cpp data.cpp $(CXXFLAGS)
TARGET  = exec_print

all: $(TARGET)

exec_print: *.cpp $(DIR_DATA)/*
	g++ $(DATA_SRC) -o $@

clean:
	rm -f $(TARGET)
