#pragma once

#include "inode.hpp"

namespace ast {
    class FunctionCall final : public INode {
        std::string function_;
        node_list_t args_;

    public:
        explicit FunctionCall(const std::string& function, const node_list_t& args);

        std::string getFunction() const;

        const node_list_t& getArgs() const noexcept;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif
    };

    node_ptr_t makeFunctionCall(const std::string& name, const node_list_t& args);
}  // namespace ast
