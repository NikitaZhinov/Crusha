#pragma once

#include "inode.hpp"

namespace ast {
    class Variable final : public INode {
        std::string name_;
        std::string type_;

    public:
        explicit Variable(const std::string& name, const std::string& type);

        std::string getName() const;

        std::string getType() const;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif
    };

    node_ptr_t makeVariable(const std::string& name, const std::string& type);
}  // namespace ast
