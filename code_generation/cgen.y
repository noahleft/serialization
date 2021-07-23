%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern char *yytext;
extern FILE* yyin;

void yyerror(const char* s);
%}

%token S_BLEFT S_BRIGHT S_SEMI S_COLON
%token S_LESSTHAN S_GREATERTHAN S_ASTERISK S_PRAGMA
%token S_CLASS S_PUBLIC
%token S_DOUBLE S_INT S_BOOL
%token S_STD
%token S_STRING S_VECTOR
%token <strval> U_STRING

%union {
    char*   strval;
}

%start content

%%

content:
	   | content class_block
;

class_block: S_CLASS {
		printf("SER_SCOPE_BEGIN\n");
	} class_name S_BLEFT class_content {
		printf("}\n");
	} S_BRIGHT {
		printf("SER_SCOPE_END\n\n");
	} S_SEMI
;

class_name: U_STRING {
		printf("template<class Archive>\n");
		printf("void serialize(Archive & ar, %s & obj, const unsigned int version) {", $1);
	} inheritance { printf("\n"); }
;

inheritance: 
	| S_COLON S_PUBLIC U_STRING { 
		printf("\nboost::serialization::base_object<%s>(obj);", $3);
	}
;

class_content:
	| class_content member_variable
	| class_content pragma
;

pragma: S_PRAGMA U_STRING {
		printf("ar.template register_type<%s>();\n", $2);
	}
;

member_variable: data_type data_name S_SEMI
;

stdstring: S_STD S_COLON S_COLON S_STRING
;

stdvector: S_STD S_COLON S_COLON S_VECTOR S_LESSTHAN U_STRING S_ASTERISK S_GREATERTHAN

data_type: S_DOUBLE
	| S_INT
	| S_BOOL
	| stdstring
	| stdvector
	| U_STRING
;

data_name: U_STRING { printf("ar & obj.%s;\n", $1); }
;

%%

int main(int argc, char const *argv[]) {
	if (argc<2) {
		printf("./cgen_parser <input files> <output file>\n");
		exit(1);
	}

	yyin = fopen(argv[1], "r");
	if(!yyin) { exit(1); }

	printf("#ifndef DATA_SER_HPP\n");
	printf("#define DATA_SER_HPP\n");
	printf("#include \"data.hpp\"\n");
	printf("#include \"codegen_macro.hpp\"\n");

	do {
		yyparse();
	} while(!feof(yyin));

	printf("#endif\n");

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}