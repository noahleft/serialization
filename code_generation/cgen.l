%option noyywrap

%{
#include <stdio.h>

#define YY_DECL int yylex()

#include "cgen_parser.h"

%}

%%

[ \t\n]+	 ;
"{"      {return S_BLEFT;}
"}"      {return S_BRIGHT;}
";"      {return S_SEMI;}
":"      {return S_COLON;}
"<"      {return S_LESSTHAN;}
">"      {return S_GREATERTHAN;}
"*"      {return S_ASTERISK;}
"#pragma" {return S_PRAGMA;}
"class"  {return S_CLASS;}
"public" {return S_PUBLIC;}
"double" {return S_DOUBLE;}
"int"    {return S_INT;}
"bool"   {return S_BOOL;}
"std"    {return S_STD;}
"string"    {return S_STRING;}
"vector" {return S_VECTOR;}

[a-zA-Z0-9_]+       {yylval.strval = strdup(yytext); return U_STRING;}
%%