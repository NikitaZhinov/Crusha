#pragma once

#include <FlexLexer.h>

#include "ast/inode.hpp"
#include "crc.tab.hh"

class Driver final {
    FlexLexer* plex_;
    std::string file_name_;
    ast::node_ptr_t root_;

public:
    Driver(FlexLexer* plex, const std::string_view& file_name);

    yy::parser::token_type yylex(yy::parser::semantic_type* yylval);

    bool parse();

    std::string getFileName() const;
    
    void setAst(ast::node_ptr_t&& ast) noexcept;

    const ast::node_ptr_t& ast() const noexcept;
};
