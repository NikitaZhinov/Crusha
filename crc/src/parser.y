%language "c++"

%skeleton "lalr1.cc"

%defines
%define api.value.type variant
%define api.value.automove

%param {Driver* driver}

%code requires {
	#include <optional>
	#include <string>
	#include <utility>

	#include "ast/ast.hpp"

	class Driver;
}

%code {
	#include <print>
	#include <string_view>
	
	#include "driver.hpp"

	namespace yy {
		parser::token_type yylex(parser::semantic_type* yylval, Driver* driver);
	}
}

%token
	KW_FUNC			"func"
	KW_LET			"let"
	KW_RETURN		"return"
	KW_NEW			"new"
	KW_CLASS		"class"

	COLON			":"
	LEFT_ARROW		"->"

	PLUS            "+"
	MINUS           "-"
	MULTIPLICATION	"*"
	DIVISION        "/"
	ASSIGNMENT		"="

	LP				"("
	RP				")"
	LB				"{"
	RB				"}"

	COMMA			","
	SCOLON			";"

	UNKNOW
;

%token <std::string> NAME
%token <std::string> LITERAL_INT
%token <std::string> LITERAL_FLOAT
%token <std::string> LITERAL_STRING
%token <std::string> LITERAL_CHAR
%token <std::string> COMMENT
%token <std::string> COMMENT_BLOCK

%left PLUS MINUS
%left MULTIPLICATION DIVISION

%type <ast::node_ptr_t>		module func var scope stmt expr assignment assigned literal func_call arith_expr operation class class_field class_func module_stmt
%type <ast::node_list_t>	func_vars func_var_list stmts func_params func_params_list class_stmts module_stmts

%start module

%%

module :			module_stmts											{ driver->setAst(ast::makeModule(driver->getFileName(), $1)); }
					| %empty												{ driver->setAst(ast::makeModule(driver->getFileName(), {})); }

module_stmts :		module_stmts module_stmt								{ $$ = $1; $$.push_back($2); }
					| module_stmt											{ $$.push_back($1); }

module_stmt :		func													{ $$ = $1; }
					| class													{ $$ = $1; }

func :				KW_FUNC NAME LP func_vars RP scope						{ $$ = ast::makeFunction($2, $4, "", $6); }
					| KW_FUNC NAME LP func_vars RP LEFT_ARROW NAME scope	{ $$ = ast::makeFunction($2, $4, $7, $8); }

func_vars :			%empty													{ $$ = {}; }
					| func_var_list											{ $$ = $1; }

func_var_list :		var														{ $$.push_back($1); }
					| func_var_list COMMA var								{ $$ = $1; $$.push_back($3); }

var :				KW_LET NAME COLON NAME									{ $$ = ast::makeVariable($2, $4); }
					| KW_LET NAME											{ $$ = ast::makeVariable($2, ""); }

scope :				LB stmts RB												{ $$ = ast::makeScope($2); }

stmts :				%empty													{ $$ = {}; }
					| stmts stmt											{ $$ = $1; $$.push_back($2); }

stmt :				expr SCOLON												{ $$ = $1; }
					| scope													{ $$ = $1; }

expr :				%empty													{ $$ = nullptr; }
					| assignment											{ $$ = $1; }
					| func_call												{ $$ = $1; }
					| KW_RETURN arith_expr									{ $$ = ast::makeReturn($2); }

assignment :		assigned ASSIGNMENT arith_expr							{ $$ = ast::makeAssignment($1, $3); }

assigned :			var														{ $$ = $1; }
					| NAME													{ $$ = ast::makeName($1); }

literal :			LITERAL_INT												{ $$ = ast::makeLiteral(ast::INT, $1); }
					| LITERAL_FLOAT											{ $$ = ast::makeLiteral(ast::FLOAT, $1); }
					| LITERAL_STRING										{ $$ = ast::makeLiteral(ast::STRING, $1); }
					| LITERAL_CHAR											{ $$ = ast::makeLiteral(ast::CHAR, $1); }

func_call :			NAME LP func_params RP									{ $$ = ast::makeFunctionCall($1, $3); }

func_params :		%empty													{ $$ = {}; }
					| func_params_list										{ $$ = $1; }

func_params_list :	arith_expr												{ $$.push_back($1); }
					| func_params_list COMMA arith_expr						{ $$ = $1; $$.push_back($3); }

arith_expr :		arith_expr PLUS arith_expr								{ $$ = ast::makeBinaryOperator(ast::PLUS, $1, $3); }
					| arith_expr MINUS arith_expr							{ $$ = ast::makeBinaryOperator(ast::MINUS, $1, $3); }
					| arith_expr MULTIPLICATION arith_expr					{ $$ = ast::makeBinaryOperator(ast::MULT, $1, $3); }
					| arith_expr DIVISION arith_expr						{ $$ = ast::makeBinaryOperator(ast::DIV, $1, $3); }
					| operation												{ $$ = $1; }

operation :			literal													{ $$ = $1; }
					| NAME													{ $$ = ast::makeName($1); }
					| func_call												{ $$ = $1; }
					| KW_NEW NAME											{ $$ = ast::makeNew($2, {}); }
					| KW_NEW NAME LP func_params RP							{ $$ = ast::makeNew($2, $4); }

class :				KW_CLASS NAME LB class_stmts RB							{ $$ = ast::makeClass($2, $4); }

class_stmts :		class_field												{ $$.push_back($1); }
					| class_func											{ $$.push_back($1); }

class_field :		var														{ $$ = $1; }

class_func :		func													{ $$ = $1; }

%%

namespace yy {
	parser::token_type yylex(parser::semantic_type* yylval, Driver* driver) {
		return driver->yylex(yylval);
	}

	void parser::error(const std::string& err) {
		std::println("{}", err);
	}
}
