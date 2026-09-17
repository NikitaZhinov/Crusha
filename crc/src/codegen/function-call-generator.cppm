module;

#include "ast/ast.hpp"

export module codegen.function_call_generator;

import codegen.inode_generator;
import codegen.context;

namespace codegen {
    class FunctionCallGenerator final : public INodeGenerator {
        std::string generateIRL(const Context& ctx, ast::node_ptr_t node,
                                CompileTimeMemory& memory) const override {
            auto m_node = std::static_pointer_cast<ast::FunctionCall>(node);

            auto&& func_name = m_node->getFunction();

            if (!memory.isType(func_name)) {
                throw std::runtime_error("undefined type");
            }

            auto&& func = memory.getType(func_name);

            auto operator_name = std::format("{}.operator().", func_name);

            std::string code;

            std::vector<std::size_t> args_types;
            for (auto&& param : m_node->getArgs()) {
                code.append(ctx.getIRL(param, memory));
                args_types.push_back(memory.getLastRetrunedTypeId());
                operator_name.append(memory.getLastRetrunedType().name);
            }

            bool is_has = false;

            for (auto&& op : func.operators) {
                if (op.kind == CALL && op.args.size() == args_types.size()) {
                    bool is_ok = true;

                    for (std::size_t i = 0, max_i = args_types.size(); i < max_i; ++i) {
                        if (args_types[i] != op.args[i]) {
                            is_ok = false;
                        }
                    }

                    if (is_ok) {
                        is_has = true;
                        break;
                    }
                }
            }

            if (!is_has) {
                throw std::runtime_error("can not find overload");
            }

            code.append(std::format("call {}\n", operator_name));

            return code;
        }

    public:
        ast::NodeKind getNodeKind() const noexcept override {
            return ast::NodeKind::FUNCTION_CALL;
        }
    };
}  // namespace codegen
