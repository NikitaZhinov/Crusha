module;

#include "ast/ast.hpp"

export module codegen.name_generator;

import codegen.context;
import codegen.inode_generator;

namespace codegen {
    class NameGenerator final : public INodeGenerator {
        std::string generateIRL(const Context& ctx, ast::node_ptr_t node,
                                CompileTimeMemory& memory) const override {
            auto m_node = std::static_pointer_cast<ast::Name>(node);

            std::string code = std::format("mov rvr {}\n", m_node->getValue());

            return code;
        }

    public:
        ast::NodeKind getNodeKind() const noexcept override {
            return ast::NodeKind::NAME;
        }
    };
}  // namespace codegen
