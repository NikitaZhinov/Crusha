module;

#include "ast/ast.hpp"

export module codegen.new_generator;

import codegen.context;
import codegen.inode_generator;

export namespace codegen {
    class NewGenerator final : public INodeGenerator {
        std::string generateIRL(const Context& ctx, ast::node_ptr_t node,
                                CompileTimeMemory& memory) const override {
            auto m_node = std::static_pointer_cast<ast::New>(node);

            std::string code = std::format("new {}\n", m_node->getType());



            code.append(std::format("call {}_ctor", m_node->getType()));

            return code;
        }

    public:
        ast::NodeKind getNodeKind() const noexcept override {
            return ast::NodeKind::NEW;
        }
    };
}  // namespace codegen
