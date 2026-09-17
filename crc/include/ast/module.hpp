#pragma once

#include "inode.hpp"

namespace ast {
    class Module final : public INode {
        std::string name_;
        node_list_t funcs_;

    public:
        explicit Module(const std::string_view& name, const node_list_t& funcs_);

        std::string getName() const;

        const node_list_t& getFuncs() const noexcept;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif
    };

    node_ptr_t makeModule(const std::string_view& name, const node_list_t& funcs);
}  // namespace ast
