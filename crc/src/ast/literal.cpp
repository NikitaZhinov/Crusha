#include "ast/literal.hpp"

ast::Literal::Literal(LiteralKind literal, const std::string& value) : literal_(literal), value_(value) {}

ast::LiteralKind ast::Literal::getLiteral() const noexcept {
    return literal_;
}

std::string ast::Literal::getValue() const {
    return value_;
}

ast::NodeKind ast::Literal::getNodeKind() const noexcept {
    return NodeKind::LITERAL;
}

ast::node_ptr_t ast::makeLiteral(LiteralKind literal, const std::string& value) {
    return std::make_unique<Literal>(literal, value);
}

#ifdef AST_PRINT_

void ast::Literal::print(std::size_t indent) const {
    printTab(indent);
    std::println("Literal: literal='{}', value='{}'", static_cast<int>(literal_), value_);
}

#endif
