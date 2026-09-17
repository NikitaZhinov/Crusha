#pragma once

#include "inode.hpp"

namespace ast {
    class New final : public INode {
        std::string type_;
        node_list_t params_;

    public:
        explicit New(const std::string& type, const node_list_t& params);

        std::string getType() const;

        const node_list_t& getParams() const;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif  // AST_PRINT_
    };

    node_ptr_t makeNew(const std::string& type, const node_list_t& params);
}  // namespace ast
