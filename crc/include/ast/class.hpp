#pragma once

#include "inode.hpp"

namespace ast {
    class Class final : public INode {
        std::string name_;
        node_list_t body_;

    public:
        explicit Class(const std::string_view& name, node_list_t body);

        std::string getName() const noexcept;

        const node_list_t& getBody() const noexcept;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif
    };

    node_ptr_t makeClass(const std::string_view& name, node_list_t body);
}  // namespace ast
