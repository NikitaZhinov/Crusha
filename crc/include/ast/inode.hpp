#pragma once

#include <memory>
#include <vector>
#include <string>
#include <string_view>
#include <ranges>

#ifdef AST_PRINT_
    #include <print>
#endif

namespace ast {
    enum NodeKind {
        MODULE,
        VARIABLE,
        SCOPE,
        FUNCTION,
        ASSIGNMENT,
        BINARY_OPERATOR,
        LITERAL,
        NAME,
        FUNCTION_CALL,
        RETURN,
        NEW,
        CLASS
    };

    enum BinaryOpationKind {
        PLUS,
        MINUS,
        MULT,
        DIV
    };

    enum LiteralKind {
        INT,
        FLOAT,
        STRING,
        CHAR
    };

    class INode {
    public:
        virtual ~INode() = default;

        virtual NodeKind getNodeKind() const noexcept = 0;

#ifdef AST_PRINT_
        virtual void print(std::size_t indent) const = 0;

    protected:
        static void printTab(std::size_t indent);
#endif
    };

    using node_ptr_t = std::shared_ptr<INode>;
    using node_list_t = std::vector<node_ptr_t>;
}  // namespace ast
