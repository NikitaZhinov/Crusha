#include "driver.hpp"

Driver::Driver(FlexLexer* plex, const std::string_view& file_name) : plex_(plex), file_name_(file_name) {}

yy::parser::token_type Driver::yylex(yy::parser::semantic_type* yylval) {
    auto tt = static_cast<yy::parser::token_type>(plex_->yylex());

    switch (tt) {
        case yy::parser::token_type::NAME:
        case yy::parser::token_type::LITERAL_INT:
        case yy::parser::token_type::LITERAL_FLOAT:
        case yy::parser::token_type::LITERAL_STRING:
        case yy::parser::token_type::LITERAL_CHAR:
        case yy::parser::token_type::COMMENT:
        case yy::parser::token_type::COMMENT_BLOCK:
            yylval->emplace<std::string>(plex_->YYText());
            break;
        default:
            break;
    }

    return tt;
}

bool Driver::parse() {
    yy::parser p(this);
    bool res = p.parse();
    return !res;
}

std::string Driver::getFileName() const {
    return file_name_;
}

void Driver::setAst(ast::node_ptr_t&& ast) noexcept {
    root_ = std::move(ast);
}

const ast::node_ptr_t& Driver::ast() const noexcept {
    return root_;
}
