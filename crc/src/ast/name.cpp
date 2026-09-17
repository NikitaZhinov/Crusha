#include "ast/name.hpp"

ast::Name::Name(const std::string& value) : value_(value) {}

std::string ast::Name::getValue() const {
    return value_;
}

ast::NodeKind ast::Name::getNodeKind() const noexcept {
    return NodeKind::NAME;
}

ast::node_ptr_t ast::makeName(const std::string& value) {
    return std::make_unique<Name>(value);
}

#ifdef AST_PRINT_

void ast::Name::print(std::size_t indent) const {
    printTab(indent);
    std::println("Name: value='{}'", value_);
}

#endif
