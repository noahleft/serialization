
all: exec_boost exec_protobuf

exec_boost: *.cpp data/* boost_serialization/*
	g++ -Idata -Iboost_serialization -DBOOST_EXAMPLE main.cpp -o $@ -lboost_serialization

exec_protobuf: *.cpp data/* protobuf/*
	protoc -I=protobuf --cpp_out=protobuf protobuf/addressbook.proto
	g++ -Idata -Iprotobuf -DPROTOBUF_EXAMPLE -std=c++11 main.cpp protobuf/*.cc -o $@ -lprotobuf

clean:
	rm exec_* -f
	rm protobuf/*.h protobuf/*.cc
