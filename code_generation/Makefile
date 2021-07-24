

CXXFLAGS = -std=c++11
SOURCES  = cgen_parser

all: $(SOURCES)

cgen_parser: $(DIR_CGEN)/*
	bison --defines=cgen_parser.h --output=cgen_parser.cc cgen.y
	flex --outfile=cgen_lex.yy.cc cgen.l
	g++ cgen_parser.cc cgen_lex.yy.cc -o $@

clean:
	rm -f $(SOURCES)
	rm -f cgen_parser.*
	rm -f cgen_lex.yy.cc