#include "../../include/parser/function.h"

#include <stdexcept>

namespace crc {
    bool Function::_isArgExist(const std::wstring& name) {
        for (const Argument& arg : _args) {
            if (arg.name == name) {
                return true;
            }
        }
        return false;
    }

    Function::Function() : _return_type(Dictionary::Void), _expected(Name) {}

    Function::Function(const std::wstring& name) : _name(name), _return_type(Dictionary::Void), _expected(Args) {}

    Function::Function(const std::wstring& name, const std::vector<Argument> args) :
        _name(name),
        _args(args),
        _return_type(Dictionary::Void),
        _expected(ReturnType) {}

    Function::Function(const std::wstring& name, const std::vector<Argument> args, Dictionary::TypeId return_type) :
        _name(name),
        _args(args),
        _return_type(return_type),
        _expected(Block) {}

    void Function::setName(const std::wstring& name) {
        _name = name;
        _expected = StartArgs;
    }

    void Function::setArgs(const std::vector<Argument>& args) {
        _args = args;
        _expected = ReturnTypeOperator;
    }

    void Function::setReturnType(Dictionary::TypeId return_type) {
        _return_type = return_type;
        _expected = StartBlock;
    }

    void Function::setBlock(const std::list<ParsingTree>& block) {
        _block = block;
        _expected = End;
    }

    void Function::setExpected(Expected expected) {
        _expected = expected;
    }

    std::wstring Function::getName() const {
        return _name;
    }

    std::vector<Function::Argument> Function::getArgs() const {
        return _args;
    }

    Dictionary::TypeId Function::getReturnType() const {
        return _return_type;
    }

    std::list<ParsingTree> Function::getBlock() const {
        return _block;
    }

    Function::Expected Function::getExpected() const {
        return _expected;
    }

    void Function::addArg() {
        _args.push_back(Argument());
        _expected = ArgName;
    }

    void Function::setArgType(Dictionary::TypeId type) {
        if (_args.empty()) {
            throw std::runtime_error("the argument to which the type is assigned was not found");
        }
        _args.back().type = type;
        _expected = ArgName;
    }

    void Function::setArgName(const std::wstring& name) {
        if (_args.empty()) {
            throw std::runtime_error("the argument to which the name is assigned was not found");
        }
        if (_isArgExist(name)) {
            throw std::runtime_error("an argument with this name already exists");
        }
        _args.back().name = name;
        _expected = EndArgs;
    }

    void Function::addArg(const Argument& arg) {
        addArg();
        setArgType(arg.type);
        setArgName(arg.name);
    }

    void Function::addBlockToken(const Lexer::token_t& token, const std::vector<std::wstring>& function_names) {
        if (_block.empty() || !_block.empty() && _block.back().isFull()) {
            _block.push_back(ParsingTree());
        }
        _block.back().addToken(token, function_names);
    }
}  // namespace crc
