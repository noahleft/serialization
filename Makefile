
CXXFLAGS = -std=c++11
SOURCES = exec_boost exec_codegen exec_protobuf exec_print

all: $(SOURCES)

exec_boost: *.cpp data/* boost_serialization/*
	g++ -Idata -Iboost_serialization -DBOOST_EXAMPLE $(CXXFLAGS) -o $@ \
		main.cpp data.cpp boost_exec.cpp -lboost_serialization

exec_codegen: *.cpp data/* code_generation/*
	python3 code_generation/extractSerializableType.py data/*.hpp > code_generation/serializable.list
	g++ data/data.hpp -E -o code_generation/preprocessed_data.hpp
	python3 code_generation/filterPreprocessedData.py code_generation/serializable.list code_generation/preprocessed_data.hpp code_generation/filtered_data.hpp

exec_protobuf: *.cpp data/* protobuf/*
	protoc -I=protobuf --cpp_out=protobuf protobuf/addressbook.proto
	g++ -Idata -Iprotobuf -DPROTOBUF_EXAMPLE $(CXXFLAGS) -o $@ \
		main.cpp data.cpp protobuf_exec.cpp protobuf/*.cc -lprotobuf

exec_print: *.cpp data/*
	g++ -Idata $(CXXFLAGS) main.cpp data.cpp -o $@

clean:
	rm -f $(SOURCES)
	rm -f protobuf/*.h protobuf/*.cc
	rm code_generation/preprocessed_*.hpp code_generation/*.list
