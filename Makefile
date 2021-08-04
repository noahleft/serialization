
DIR_DATA  = data
DIR_BOOST = boost_serialization
DIR_CGEN  = code_generation
DIR_PROTO = protobuf
DIR_TRACK = protobuf_tracking

CXXFLAGS = -std=c++11
DATA_SRC = -I$(DIR_DATA) main.cpp $(DIR_DATA)/data.cpp $(CXXFLAGS)
SOURCES  = exec_boost exec_codegen exec_protobuf exec_protobuf_tracking exec_print

all: $(SOURCES)

exec_boost: *.cpp $(DIR_DATA)/* $(DIR_BOOST)/*
	g++ -I$(DIR_BOOST) -DBOOST_EXAMPLE $(DATA_SRC) -o $@ \
		exec_boost.cpp -lboost_serialization

cgen_parser: $(DIR_CGEN)/* $(DIR_DATA)/*
	make -C $(DIR_CGEN)

exec_codegen: *.cpp $(DIR_DATA)/* $(DIR_CGEN)/* cgen_parser
	python3 $(DIR_CGEN)/extractSerializableType.py $(DIR_DATA)/*.hpp > $(DIR_CGEN)/serializable.list
	g++ $(DIR_DATA)/data.hpp -E -o $(DIR_CGEN)/preprocessed_data.hpp
	python3 $(DIR_CGEN)/filterPreprocessedData.py $(DIR_CGEN)/serializable.list $(DIR_CGEN)/preprocessed_data.hpp $(DIR_CGEN)/filtered_data.hpp
	./$(DIR_CGEN)/cgen_parser $(DIR_CGEN)/filtered_data.hpp > $(DIR_CGEN)/data_ser.hpp
	g++ -I$(DIR_CGEN) -DCODEGEN_EXAMPLE $(DATA_SRC) -o $@ \
		exec_codegen.cpp -lboost_serialization

exec_protobuf: *.cpp $(DIR_DATA)/* $(DIR_PROTO)/*
	protoc -I=$(DIR_PROTO) --cpp_out=$(DIR_PROTO) $(DIR_PROTO)/addressbook.proto
	g++ -I$(DIR_PROTO) -DPROTOBUF_EXAMPLE $(DATA_SRC) -o $@ \
		exec_protobuf.cpp protobuf/*.cc -lprotobuf

exec_protobuf_tracking: *.cpp $(DIR_DATA)/* $(DIR_TRACK)/*
	protoc -I=$(DIR_TRACK) --cpp_out=$(DIR_TRACK) $(DIR_TRACK)/addressbook.proto
	g++ -I$(DIR_TRACK) -DPROTOBUF_TRACK_EXAMPLE $(DATA_SRC) -o $@ \
		exec_protobuf_tracking.cpp protobuf_tracking/*.cc -lprotobuf

exec_print: *.cpp $(DIR_DATA)/*
	g++ $(DATA_SRC) -o $@

clean:
	rm -f $(SOURCES)
	rm -f $(DIR_PROTO)/*.h $(DIR_PROTO)/*.cc
	rm -f $(DIR_CGEN)/preprocessed_*.hpp $(DIR_CGEN)/*.list
	rm -f $(DIR_CGEN)/data_ser.hpp
	make -C $(DIR_CGEN) clean
