#include "ast/new.hpp"

ast::New::New(const std::string& type, const node_list_t& params) : type_(type), params_(params) {}

std::string ast::New::getType() const {
    return type_;
}

const ast::node_list_t& ast::New::getParams() const {
    return params_;
}

ast::NodeKind ast::New::getNodeKind() const noexcept {
    return NodeKind::NEW;
}

#ifdef AST_PRINT_

void ast::New::print(std::size_t indent) const {
    printTab(indent);
    std::println("New: type='{}'", type_);

    printTab(indent);
    std::println("Params:");

    for (auto&& param : params_) {
        param->print(indent + 1);
    }
}

#endif

ast::node_ptr_t ast::makeNew(const std::string& type, const node_list_t& params) {
    return std::make_shared<New>(type, params);
}
