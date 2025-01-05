#pragma once

#include "type.h"
#include "parsing-tree.h"

#include <list>
#include <string>
#include <vector>

namespace crc {
    class Function {
    public:
        struct Argument {
            Type::TypeId type = Type::Void;
            std::wstring name;
        };

        enum Expected {
            Name = 0,
            StartArgs,
            Args,
            NewArg,
            ArgTypeOperator,
            ArgType,
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
        Type::TypeId _return_type;
        std::list<ParsingTree> _block;
        Expected _expected;

        bool _isArgExist(const std::wstring &name);

    public:
        Function();
        Function(const std::wstring &name);
        Function(const std::wstring &name, const std::vector<Argument> args);
        Function(const std::wstring &name, const std::vector<Argument> args, Type::TypeId return_type);

        void setName(const std::wstring &name);
        void setArgs(const std::vector<Argument> &args);
        void setReturnType(Type::TypeId return_type);
        void setBlock(const std::list<ParsingTree> &block);
        void setExpected(Expected expected);

        std::wstring getName() const;
        std::vector<Argument> getArgs() const;
        Type::TypeId getReturnType() const;
        std::list<ParsingTree> getBlock() const;
        Expected getExpected() const;

        void addArg();
        void setArgType(Type::TypeId type);
        void setArgName(const std::wstring &name);
        void addArg(const Argument &arg);
    };
}  // namespace crc
