module;

#include "ast/inode.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>

export module codegen.compile_time_memory;

export namespace codegen {
    struct Variable final {
        std::string name;
        std::size_t type_id = 0;
    };

    enum OperatorKind {
        ASSINGMENT,
        CALL
    };

    OperatorKind str_to_operator(const std::string_view& str) {
        if (str == "=") {
            return ASSINGMENT;
        }

        if (str == "()") {
            return CALL;
        }

        throw std::runtime_error("undefined operator");
    }

    struct TypeOperator final {
        OperatorKind kind = ASSINGMENT;
        std::vector<std::size_t> args;
        bool is_static = false;
    };

    struct Type final {
        static std::size_t last_id;

        std::size_t id;
        std::string name;
        std::vector<Variable> variables;
        std::vector<std::size_t> methods;
        std::vector<TypeOperator> operators;

        Type(const std::string& name_ = "", const std::vector<Variable>& variables_ = {},
             const std::vector<std::size_t>& methods_ = {},
             const std::vector<TypeOperator>& operators_ = {}) :
            id(last_id),
            name(name_),
            variables(variables_),
            methods(methods_),
            operators(operators_) {
            ++last_id;
        }
    };

    std::size_t Type::last_id = 0;

    struct Namesapce final {
        std::string name;
        std::vector<Type> types;
    };

    struct Scope final {
        std::unordered_map<std::string, Variable> variables;
    };

    class CompileTimeMemory final {
        std::unordered_map<std::string, Namesapce> namespaces_;
        std::unordered_map<std::size_t, Type> types_;
        std::unordered_map<std::string, std::size_t> type_ids_;
        std::vector<Scope> scopes_;

        std::size_t last_returned_type_ = 0;

    public:
        CompileTimeMemory() {
            addType("void");
        }

        bool isNamespace(const std::string& name) const {
            return namespaces_.count(name) != 0;
        }

        bool isType(std::size_t name) const {
            return types_.count(name) != 0;
        }

        bool isType(const std::string& name) const {
            return type_ids_.count(name) != 0;
        }

        std::optional<decltype(Scope::variables)::iterator> findVariable(const std::string& name) {
            for (auto it = scopes_.rbegin(), last_it = scopes_.rend(); it != last_it; ++it) {
                if (it->variables.count(name) != 0) {
                    return it->variables.find(name);
                }
            }

            return std::nullopt;
        }

        Namesapce& getNamesapce(const std::string& name) {
            return namespaces_[name];
        }

        Type& getType(std::size_t id) {
            return types_[id];
        }

        Type& getType(const std::string& name) {
            return getType(type_ids_[name]);
        }

        Scope& getCurentScope() {
            return scopes_.back();
        }

        Type& getVariableType(decltype(Scope::variables)::iterator it) {
            return getType(it->second.type_id);
        }

        std::size_t getLastRetrunedTypeId() const noexcept {
            return last_returned_type_;
        }

        Type& getLastRetrunedType() {
            return types_[last_returned_type_];
        }

        Namesapce& addNamespace(const std::string& name) {
            if (namespaces_.count(name) == 0) {
                return namespaces_.insert({ name, Namesapce {} }).first->second;
            }

            return getNamesapce(name);
        }

        Type& addType(const std::string& name, const std::vector<Variable>& variables = {},
                      const std::vector<std::size_t>& methods = {},
                      const std::vector<TypeOperator>& operators = {}) {
            auto&& type = Type { name, variables, methods, operators };
            return types_.insert({ type.id, type }).first->second;
        }

        Scope& addScope() {
            return scopes_.emplace_back(Scope {});
        }

        void addVariable(Scope& scope, const std::string& name, std::size_t type_id) {
            scope.variables.insert({
                name, Variable { name, type_id }
            });
        }

        void setLastRetrunedType(std::size_t last_returned_type) noexcept {
            last_returned_type_ = last_returned_type;
        }
    };
}  // namespace codegen
