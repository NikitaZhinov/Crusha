#pragma once

#include <string>

namespace crc {
    class Token {
    public:
        enum TokenType {
            Undefined = 0,
            Var,
            Func,
            Name,
            Operator,
            Type,
            RoundBracketOpen,
            RoundBracketClose,
            SquareBracketOpen,
            SquareBracketClose,
            CurlyBracketOpen,
            CurlyBracketClose,
            Int,
            Float,
            Text,
            End
        };

    private:
        TokenType _type = Undefined;
        std::wstring _name;

        void _defineType();

    public:
        Token() = default;
        Token(const std::wstring& name);

        void setName(const std::wstring& name);
        void setType(TokenType type);

        TokenType getType();
        std::wstring getName();
    };
}  // namespace crc
