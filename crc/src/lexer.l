%option c++
%option yyclass="Lexer"

%{

#include "lexer.hpp"

%}

WS				[ \t\r\v]+
DIGIT			[0-9]
CHARS			[A-Za-z_]
DIGIT_AND_CHARS	[A-Za-z0-9_]
COMM			"//".*"\n"
MULCOMM			"/*".*"*/"
STR				\"[^"]*\"
CHAR			\'[^'\\]|\\[A-Za-z0-9]\'

%%

\n							nextRow();
{WS}						nextCol(yyleng);

{DIGIT}*					return processLiteralInt(yyleng);
{DIGIT}"."{DIGIT}			return processLiteralFloat(yyleng);
"."{DIGIT}					return processLiteralFloat(yyleng);

{STR}						return processLiteralString(yyleng);
{CHAR}						return processLiteralChar(yyleng);

{COMM}						return processComment(yyleng);
{MULCOMM}					return processCommentBlock(yyleng);

"func"						return processKWFunc(yyleng);
"let"						return processKWLet(yyleng);
"return"					return processKWReturn(yyleng);
"new"						return processKWNew(yyleng);
"class"						return processKWClass(yyleng);

":"							return processColon(yyleng);
"->"						return processLeftArrow(yyleng);

"+"							return processPlus(yyleng);
"-"							return processMinus(yyleng);
"*"							return processMultiplication(yyleng);
"/"							return processDivision(yyleng);
"="							return processAssignment(yyleng);

"("							return processLP(yyleng);
")"							return processRP(yyleng);
"{"							return processLB(yyleng);
"}"							return processRB(yyleng);

","							return processComma(yyleng);
";"							return processScolon(yyleng);

{CHARS}*{DIGIT_AND_CHARS}*	return processName(yyleng);

.							processUnknow();

<<EOF>>						{ return 0; }

%%
