#include "ast/function-call.hpp"

ast::FunctionCall::FunctionCall(const std::string& function, const node_list_t& args) :
    function_(function),
    args_(args) {}

std::string ast::FunctionCall::getFunction() const {
    return function_;
}

const ast::node_list_t& ast::FunctionCall::getArgs() const noexcept {
    return args_;
}

ast::NodeKind ast::FunctionCall::getNodeKind() const noexcept {
    return NodeKind::FUNCTION_CALL;
}

ast::node_ptr_t ast::makeFunctionCall(const std::string& name, const node_list_t& args) {
    return std::make_unique<FunctionCall>(name, args);
}

#ifdef AST_PRINT_

void ast::FunctionCall::print(std::size_t indent) const {
    printTab(indent);
    std::println("FunctionCall: function='{}'", function_);

    printTab(indent);
    std::println("Args:");
    for (const auto& arg : args_) {
        if (arg) {
            arg->print(indent + 1);
        }
    }
}

#endif
