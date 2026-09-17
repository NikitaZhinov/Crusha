module;

#include "ast/module.hpp"

#include <cassert>
#include <format>

export module codegen.module_generator;

import codegen.inode_generator;
import codegen.context;

export namespace codegen {
    class ModuleGenerator final : public INodeGenerator {
        std::string generateIRL(const Context& ctx, ast::node_ptr_t node,
                              CompileTimeMemory& memory) const override {
            auto m_node = std::static_pointer_cast<ast::Module>(node);

            std::string code;

            for (auto&& func : m_node->getFuncs()) {
                auto func_asm = ctx.getIRL(func, memory);
                code.append(func_asm);
            }
            
            return code;
        }

    public:
        ast::NodeKind getNodeKind() const noexcept override {
            return ast::MODULE;
        }
    };
}  // namespace codegen
