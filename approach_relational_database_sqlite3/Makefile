
DIR_DATA  = data

CXXFLAGS = -std=c++11
DATA_SRC = -I$(DIR_DATA) $(DIR_DATA)/main.cpp $(DIR_DATA)/data.cpp $(CXXFLAGS)
TARGET  = exec_sqlite

all: $(TARGET)

exec_sqlite: *.cpp $(DIR_DATA)/*
	g++ -DSERIALIZE $(DATA_SRC) -o $@ \
		exec_sqlite3.cpp -lsqlite3

clean:
	rm -f $(TARGET)
