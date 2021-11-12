
DIR_TMP = tmpdir
DIR_DATA = data
CXXFLAGS = -std=c++11
DATA_SRC = -I. -I$(DIR_DATA) -I$(DIR_TMP) $(DIR_DATA)/main.cpp $(DIR_DATA)/data.cpp $(CXXFLAGS)
TARGET = exec_codegen

all: $(TARGET)

cgen_parser: cgen.*
	bison --defines=cgen_parser.h --output=cgen_parser.cc cgen.y
	flex --outfile=cgen_lex.yy.cc cgen.l
	g++ cgen_parser.cc cgen_lex.yy.cc -o $@

exec_codegen: *.cpp $(DIR_DATA)/* cgen_parser
	mkdir $(DIR_TMP)
	python3 extractSerializableType.py $(DIR_DATA)/*.hpp > $(DIR_TMP)/serializable.list
	g++ $(DIR_DATA)/data.hpp -E -o $(DIR_TMP)/preprocessed_data.hpp
	python3 filterPreprocessedData.py $(DIR_TMP)/serializable.list $(DIR_TMP)/preprocessed_data.hpp $(DIR_TMP)/filtered_data.hpp
	./cgen_parser $(DIR_TMP)/filtered_data.hpp > $(DIR_TMP)/data_ser.hpp
	g++ -DSERIALIZE $(DATA_SRC) -o $@ \
		exec_codegen.cpp -lboost_serialization

clean:
	rm -f $(TARGET)
	rm -f cgen_parser*
	rm -f cgen_lex.yy.cc
	rm -rf $(DIR_TMP)
