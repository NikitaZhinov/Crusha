#include "ast/class.hpp"

ast::Class::Class(const std::string_view& name, node_list_t body) : name_(name), body_(body) {}

std::string ast::Class::getName() const noexcept {
    return name_;
}

const ast::node_list_t& ast::Class::getBody() const noexcept {
    return body_;
}

ast::NodeKind ast::Class::getNodeKind() const noexcept {
    return NodeKind::CLASS;
}

#ifdef AST_PRINT_

void ast::Class::print(std::size_t indent) const {
    printTab(indent);
    std::println("Class: name='{}'", name_);

    printTab(indent);
    std::println("Body:");
    for (auto&& stmt : body_) {
        stmt->print(indent + 1);
    }
}

#endif  // AST_PRINT_

ast::node_ptr_t ast::makeClass(const std::string_view& name, node_list_t body) {
    return std::make_shared<ast::Class>(name, body);
}
