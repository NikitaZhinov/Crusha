#include "ast/function.hpp"

#include <format>

ast::Function::Function(const std::string& name, const node_list_t& params, const std::string& return_type,
                        node_ptr_t body) :
    name_(name),
    params_(params),
    return_type_(return_type),
    body_(body) {}

std::string ast::Function::getName() const {
    return name_;
}

const ast::node_list_t& ast::Function::getParams() const noexcept {
    return params_;
}

std::string ast::Function::getReturnType() const {
    return return_type_;
}

const ast::node_ptr_t& ast::Function::getBody() const noexcept {
    return body_;
}

ast::NodeKind ast::Function::getNodeKind() const noexcept {
    return NodeKind::FUNCTION;
}

ast::node_ptr_t ast::makeFunction(const std::string& name, const node_list_t& params,
                                  const std::string& return_type, node_ptr_t body) {
    return std::make_unique<Function>(name, params, return_type, body);
}

#ifdef AST_PRINT_

void ast::Function::print(std::size_t indent) const {
    printTab(indent);
    std::println("Function: name='{}', return-type='{}'", name_, return_type_);

    printTab(indent);
    std::println("Params:");
    for (const auto& param : params_) {
        if (param) {
            param->print(indent + 1);
        }
    }

    printTab(indent);
    std::println("Body:");
    if (body_) {
        body_->print(indent + 1);
    }
}

#endif
