#pragma once

#include "inode.hpp"

namespace ast {
    class Literal final : public INode {
        LiteralKind literal_;
        std::string value_;

    public:
        explicit Literal(LiteralKind literal, const std::string& value);

        LiteralKind getLiteral() const noexcept;

        std::string getValue() const;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif
    };

    node_ptr_t makeLiteral(LiteralKind literal, const std::string& value);
}  // namespace ast
