module;

#include "ast/inode.hpp"

#include <cassert>

export module codegen.inode_generator;

import codegen.compile_time_memory;

export namespace codegen {
    class Context;

    class INodeGenerator {
    protected:
        virtual std::string generateIRL(const Context& ctx, ast::node_ptr_t node,
                                        CompileTimeMemory& memory) const = 0;

    public:
        virtual ~INodeGenerator() = default;

        virtual ast::NodeKind getNodeKind() const noexcept = 0;

        virtual std::string getIRL(const Context& ctx, ast::node_ptr_t node,
                                   CompileTimeMemory& memory) const {
            assert(getNodeKind() != node->getNodeKind());

            return generateIRL(ctx, node, memory);
        }
    };
}  // namespace codegen
