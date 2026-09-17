module;

#include "ast/ast.hpp"

export module codegen.variable_generator;

import codegen.context;
import codegen.inode_generator;

export namespace codegen {
    class VariableGenerator final : public INodeGenerator {
        std::string generateIRL(const Context& ctx, ast::node_ptr_t node,
                                CompileTimeMemory& memory) const override {
            auto m_node = std::static_pointer_cast<ast::Variable>(node);

            std::string code = std::format("let {} {}\n", m_node->getName(), m_node->getType());
            code.append(std::format("mov rvr {}", m_node->getName()));

            return code;
        }

    public:
        ast::NodeKind getNodeKind() const noexcept override {
            return ast::NodeKind::VARIABLE;
        }
    };
}  // namespace codegen
