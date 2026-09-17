#include "ast/variable.hpp"

ast::Variable::Variable(const std::string& name, const std::string& type) : name_(name), type_(type) {}

std::string ast::Variable::getName() const {
    return name_;
}

std::string ast::Variable::getType() const {
    return type_;
}

ast::NodeKind ast::Variable::getNodeKind() const noexcept {
    return NodeKind::VARIABLE;
}

ast::node_ptr_t ast::makeVariable(const std::string& name, const std::string& type) {
    return std::make_unique<Variable>(name, type);
}

#ifdef AST_PRINT_

void ast::Variable::print(std::size_t indent) const {
    printTab(indent);
    std::println("Variable: name='{}', type='{}'", name_, type_);
}

#endif
