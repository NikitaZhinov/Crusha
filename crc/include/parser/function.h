#pragma once

#include "dictionary.h"
#include "parsing-tree.h"

#include <list>
#include <string>
#include <vector>

namespace crc {
    class Function {
    public:
        struct Argument {
            Dictionary::TypeId type = Dictionary::Void;
            std::wstring name;
        };

        enum Expected {
            Name = 0,
            StartArgs,
            Args,
            NewArg,
            ArgName,
            EndArgs,
            ReturnTypeOperator,
            ReturnType,
            StartBlock,
            Block,
            End
        };

    private:
        std::wstring _name;
        std::vector<Argument> _args;
        Dictionary::TypeId _return_type;
        std::list<ParsingTree> _block;
        Expected _expected;

        bool _isArgExist(const std::wstring& name);

    public:
        Function();
        Function(const std::wstring& name);
        Function(const std::wstring& name, const std::vector<Argument> args);
        Function(const std::wstring& name, const std::vector<Argument> args, Dictionary::TypeId return_type);

        void setName(const std::wstring& name);
        void setArgs(const std::vector<Argument>& args);
        void setReturnType(Dictionary::TypeId return_type);
        void setBlock(const std::list<ParsingTree>& block);
        void setExpected(Expected expected);

        std::wstring getName() const;
        std::vector<Argument> getArgs() const;
        Dictionary::TypeId getReturnType() const;
        std::list<ParsingTree> getBlock() const;
        Expected getExpected() const;

        void addArg();
        void setArgType(Dictionary::TypeId type);
        void setArgName(const std::wstring& name);
        void addArg(const Argument& arg);

        void addBlockToken(const Lexer::token_t& token, const std::vector<std::wstring>& function_names);
    };
}  // namespace crc
