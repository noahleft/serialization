
DIR_DATA  = data
DIR_TMP = tmpdir

CXXFLAGS = -std=c++11
DATA_SRC = -I$(DIR_DATA) $(DIR_DATA)/main.cpp $(DIR_DATA)/data.cpp $(CXXFLAGS)
SOURCES  = exec_protobuf

all: $(SOURCES)

exec_protobuf: *.cpp $(DIR_DATA)/*
	mkdir $(DIR_TMP)
	protoc --cpp_out=$(DIR_TMP) addressbook.proto
	g++ -I$(DIR_TMP) -DSERIALIZE $(DATA_SRC) -o $@ \
		exec_protobuf.cpp $(DIR_TMP)/*.cc -lprotobuf

clean:
	rm -f $(SOURCES)
	rm -rf $(DIR_TMP)