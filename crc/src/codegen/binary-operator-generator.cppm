module;

#include "ast/ast.hpp"

export module codegen.binary_operator_generator;

import codegen.inode_generator;
import codegen.context;

export namespace codegen {
    class BinaryOperatorGenerator final : public INodeGenerator {
        std::string generateIRL(const Context& ctx, ast::node_ptr_t node,
                                CompileTimeMemory& memory) const override {
            auto m_node = std::static_pointer_cast<ast::BinaryOperator>(node);

            std::string code = ctx.getIRL(m_node->getLeft(), memory);

            code.append("mov lor rvr\n");

            code.append(ctx.getIRL(m_node->getRight(), memory));

            code.append("mov ror rvr\n");

            std::string op;

            switch (m_node->getOperator()) {
                case ast::PLUS:
                    op = "+";
                    break;

                case ast::MINUS:
                    op = "-";
                    break;

                case ast::MULT:
                    op = "*";
                    break;

                case ast::DIV:
                    op = "/";
                    break;
            }

            code.append(std::format("call operator_{}", op));

            return code;
        }

    public:
        ast::NodeKind getNodeKind() const noexcept override {
            return ast::NodeKind::BINARY_OPERATOR;
        }
    };
}  // namespace codegen
