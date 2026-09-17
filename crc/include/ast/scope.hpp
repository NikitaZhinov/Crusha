#pragma once

#include "inode.hpp"

namespace ast {
    class Scope final : public INode {
        node_list_t statements_;

    public:
        explicit Scope(const node_list_t& statements);

        const node_list_t& getStatemets() const noexcept;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif
    };

    node_ptr_t makeScope(const node_list_t& statements);
}  // namespace ast
