module;

#include "ast/inode.hpp"

#include <unordered_map>
#include <type_traits>

export module codegen.context;

import codegen.inode_generator;
import codegen.compile_time_memory;

export namespace codegen {
    class Context final {
        std::unordered_map<ast::NodeKind, std::shared_ptr<INodeGenerator>> generators_;

    public:
        template <class BuilderT>
            requires std::is_base_of_v<INodeGenerator, BuilderT>
        void addBuilder(ast::NodeKind kind) {
            generators_.emplace(kind, std::make_shared<BuilderT>());
        }

        std::string getIRL(ast::node_ptr_t node, CompileTimeMemory& params) const {
            return generators_.find(node->getNodeKind())->second->getIRL(*this, node, params);
        }
    };
}  // namespace codegen
