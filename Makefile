
CXXFLAGS = -std=c++11
SOURCES = exec_boost exec_protobuf exec_print

all: $(SOURCES)

exec_boost: *.cpp data/* boost_serialization/*
	g++ -Idata -Iboost_serialization -DBOOST_EXAMPLE $(CXXFLAGS) -o $@ \
		main.cpp -lboost_serialization

exec_protobuf: *.cpp data/* protobuf/*
	protoc -I=protobuf --cpp_out=protobuf protobuf/addressbook.proto
	g++ -Idata -Iprotobuf -DPROTOBUF_EXAMPLE $(CXXFLAGS) -o $@ \
		main.cpp protobuf/*.cc -lprotobuf

exec_print: *.cpp data/*
	g++ -Idata $(CXXFLAGS) main.cpp -o $@

clean:
	rm -f $(SOURCES)
	rm -f protobuf/*.h protobuf/*.cc
