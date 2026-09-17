#pragma once

#include "inode.hpp"

namespace ast {
    class Name final : public INode {
        std::string value_;

    public:
        explicit Name(const std::string& value);

        std::string getValue() const;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif
    };

    node_ptr_t makeName(const std::string& value);
}  // namespace ast
