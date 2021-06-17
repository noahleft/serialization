
all: exec_boost exec_protobuf exec_print

exec_boost: *.cpp data/* boost_serialization/*
	g++ -Idata -Iboost_serialization -DBOOST_EXAMPLE -std=c++11 main.cpp -o $@ -lboost_serialization

exec_protobuf: *.cpp data/* protobuf/*
	protoc -I=protobuf --cpp_out=protobuf protobuf/addressbook.proto
	g++ -Idata -Iprotobuf -DPROTOBUF_EXAMPLE -std=c++11 main.cpp protobuf/*.cc -o $@ -lprotobuf

exec_print: *.cpp data/*
	g++ -Idata -std=c++11 main.cpp -o $@

clean:
	rm exec_* -f
	rm protobuf/*.h protobuf/*.cc
