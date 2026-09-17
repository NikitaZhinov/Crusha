module;

#include "ast/ast.hpp"

export module codegen.assignment_generator;

import codegen.context;
import codegen.inode_generator;

export namespace codegen {
    class AssignmentGenerator final : public INodeGenerator {
        std::string generateIRL(const Context& ctx, ast::node_ptr_t node,
                                CompileTimeMemory& memory) const override {
            auto m_node = std::static_pointer_cast<ast::Assignment>(node);

            std::string code;

            code.append(ctx.getIRL(m_node->getTarget(), memory));

            code.append("mov lor rvr\n");

            code.append(ctx.getIRL(m_node->getValue(), memory));

            code.append("mov ror rvr\ncall operator=\n");

            return code;
        }

    public:
        ast::NodeKind getNodeKind() const noexcept override {
            return ast::NodeKind::ASSIGNMENT;
        }
    };
}  // namespace codegen
