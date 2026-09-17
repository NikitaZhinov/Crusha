#include "ast/module.hpp"

#include <format>
#include <cassert>

ast::Module::Module(const std::string_view& name, const node_list_t& funcs) : name_(name), funcs_(funcs) {}

std::string ast::Module::getName() const {
    return name_;
}

const ast::node_list_t& ast::Module::getFuncs() const noexcept {
    return funcs_;
}

ast::NodeKind ast::Module::getNodeKind() const noexcept {
    return NodeKind::MODULE;
}

ast::node_ptr_t ast::makeModule(const std::string_view& name, const node_list_t& funcs) {
    return std::make_unique<Module>(name, funcs);
}

#ifdef AST_PRINT_

void ast::Module::print(std::size_t indent) const {
    printTab(indent);
    std::println("Module: name='{}'", name_);

    printTab(indent);
    std::println("Functions:");

    for (const auto& func : funcs_) {
        if (func) {
            func->print(indent + 1);
        }
    }
}

#endif
