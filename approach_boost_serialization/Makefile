
DIR_DATA  = data
DIR_BOOST = boost_serialization

CXXFLAGS = -std=c++11
DATA_SRC = -I$(DIR_DATA) $(DIR_DATA)/main.cpp $(DIR_DATA)/data.cpp $(CXXFLAGS)
TARGET  = exec_boost

all: $(TARGET)

exec_boost: *.cpp $(DIR_DATA)/*
	g++ -I$(DIR_BOOST) -DSERIALIZE $(DATA_SRC) -o $@ \
		exec_boost.cpp -lboost_serialization

clean:
	rm -f $(TARGET)
