module;

#include "ast/function.hpp"
#include "ast/variable.hpp"
#include "ast/scope.hpp"

#include <cassert>
#include <format>

export module codegen.function_generator;

import codegen.inode_generator;
import codegen.context;
import codegen.compile_time_memory;

export namespace codegen {
    class FunctionGenerator final : public INodeGenerator {
        std::string generateIRL(const Context& ctx, ast::node_ptr_t node,
                                CompileTimeMemory& memory) const override {
            auto m_node = std::static_pointer_cast<ast::Function>(node);

            auto&& name = m_node->getName();
            auto&& params_ptr = m_node->getParams();

            std::vector<std::size_t> params;
            std::string name_params, param_init;
            params.reserve(params_ptr.size());

            for (auto&& param : params_ptr) {
                auto&& var = std::static_pointer_cast<ast::Variable>(param);
                auto&& type = var->getType();
                if (memory.isType(type)) {
                    name_params.append(type);
                    param_init.append(
                        std::format("\tlet {0} {1}\n\tpop rvr\n\tmov {0} rvr\n", var->getName(), type));
                    params.emplace_back(memory.getType(type));
                } else {
                    throw std::runtime_error(std::format("undefined type '{}'", type));
                }
            }

            memory.addType(name, {}, {},
                           std::vector<TypeOperator>(1, TypeOperator { OperatorKind::CALL, params }));

            std::string code = std::format("type {0}\n{0}.operator().{1}:\n", name, name_params);

            code.append("\t");

            for (auto&& stmt : std::static_pointer_cast<ast::Scope>(m_node->getBody())->getStatemets()) {
                code.append(std::format("\t{}", ctx.getIRL(stmt, memory)));
            }

            code.append("\tret\n");

            return code;
        }

    public:
        ast::NodeKind getNodeKind() const noexcept override {
            return ast::FUNCTION;
        }
    };
}  // namespace codegen
