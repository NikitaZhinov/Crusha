module;

#include "ast/scope.hpp"

export module codegen.scope_generate;

import codegen.inode_generator;
import codegen.context;

namespace codegen {
    class ScopeGenerator final : public INodeGenerator {
        std::string generateIRL(const Context& ctx, ast::node_ptr_t node,
                                CompileTimeMemory& memory) const override {
            auto m_node = std::static_pointer_cast<ast::Scope>(node);

            std::string code = "ns\n";

            for (auto&& stmt : m_node->getStatemets()) {
                code.append(ctx.getIRL(stmt, memory));
            }

            code.append("ds\n");

            return code;
        }

    public:
        ast::NodeKind getNodeKind() const noexcept override {
            return ast::NodeKind::SCOPE;
        }
    };
}  // namespace codegen
