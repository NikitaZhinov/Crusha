#pragma once

#include "inode.hpp"

namespace ast {
    class Function final : public INode {
        std::string name_;
        node_list_t params_;
        std::string return_type_;
        node_ptr_t body_;

    public:
        explicit Function(const std::string& name, const node_list_t& params, const std::string& returnType,
                          node_ptr_t body);

        std::string getName() const;

        const node_list_t& getParams() const noexcept;

        std::string getReturnType() const;

        const node_ptr_t& getBody() const noexcept;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif
    };

    node_ptr_t makeFunction(const std::string& name, const node_list_t& params,
                            const std::string& return_type, node_ptr_t body);
}  // namespace ast
