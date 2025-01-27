#include "../../include/parser/parser.h"

#include "../../include/parser/dictionary.h"
#include "../../include/error/error.h"

namespace crc {
    void Parser::_newFunction(const token_t &token) {
        if (token == L"func") {
            _functions.push_back(Function());
        }
    }

    bool Parser::_isNameExistInFuncions(const token_t &token) {
        for (const Function &func : _functions) {
            if (func.getName() == token) {
                return true;
            }
        }
        return false;
    }

    void Parser::_setNameFuntion(const token_t &token) {
        if (!Dictionary::isNameExist(token) && !_isNameExistInFuncions(token)) {
            _functions.back().setName(token);
        } else {
            Error::setTypeError(Error::Sytax);
        }
    }

    void Parser::_setStartArgsFunction(const token_t &token) {
        if (token == L"(") {
            _functions.back().setExpected(Function::Args);
        } else {
            Error::setTypeError(Error::Sytax);
        }
    }

    void Parser::_setArgsFunction(const token_t &token) {
        if (token == L")") {
            _functions.back().setExpected(Function::ReturnTypeOperator);
        } else if (Dictionary::isType(token)) {
            _functions.back().addArg();
            _functions.back().setArgType(Dictionary::getTypeId(token));
            _functions.back().setExpected(Function::ArgName);
        } else {
            Error::setTypeError(Error::Sytax);
        }
    }

    void Parser::_setNewArgFunction(const token_t &token) {
        if (Dictionary::isType(token)) {
            _functions.back().addArg();
            _functions.back().setArgType(Dictionary::getTypeId(token));
            _functions.back().setExpected(Function::ArgName);
        } else {
            Error::setTypeError(Error::Sytax);
        }
    }

    void Parser::_setArgNameFunction(const token_t &token) {
        if (!Dictionary::isNameExist(token) && !_isNameExistInFuncions(token)) {
            try {
                _functions.back().setArgName(token);
            } catch (const std::exception &) {
                Error::setTypeError(Error::Sytax);
            }
        } else {
            Error::setTypeError(Error::Sytax);
        }
    }

    void Parser::_setEndArgsFunction(const token_t &token) {
        if (token == L")") {
            _functions.back().setExpected(Function::ReturnTypeOperator);
        } else if (token == L",") {
            _functions.back().setExpected(Function::NewArg);
        } else {
            Error::setTypeError(Error::Sytax);
        }
    }

    void Parser::_setReturnTypeOperatorFunction(const token_t &token) {
        if (token == L"->") {
            _functions.back().setExpected(Function::ReturnType);
        } else if (token == L"{") {
            _functions.back().setExpected(Function::Block);
        } else {
            Error::setTypeError(Error::Sytax);
        }
    }

    void Parser::_setReturnTypeFunction(const token_t &token) {
        Dictionary::TypeId type = Dictionary::getTypeId(token);
        if (type != Dictionary::Void) {
            _functions.back().setReturnType(type);
        } else {
            Error::setTypeError(Error::Sytax);
        }
    }

    void Parser::_setStartBlockFunction(const token_t &token) {
        if (token == L"{") {
            _functions.back().setExpected(Function::Block);
        } else {
            Error::setTypeError(Error::Sytax);
        }
    }

    void Parser::_setBlockFunction(const token_t &token) {
        if (token == L"}") {
            _functions.back().setExpected(Function::End);
        } else {
            std::vector<std::wstring> function_names;
            for (const Function& func : _functions) {
                function_names.push_back(func.getName());
            }
            _functions.back().addBlockToken(token, function_names);
        }
    }

    void Parser::_tokenSyntacticAnalysis(const token_t &token) {
        if (_functions.empty() || !_functions.empty() && _functions.back().getExpected() == Function::End) {
            _newFunction(token);
        } else if (_functions.back().getExpected() == Function::Name) {
            _setNameFuntion(token);
        } else if (_functions.back().getExpected() == Function::StartArgs) {
            _setStartArgsFunction(token);
        } else if (_functions.back().getExpected() == Function::Args) {
            _setArgsFunction(token);
        } else if (_functions.back().getExpected() == Function::NewArg) {
            _setNewArgFunction(token);
        } else if (_functions.back().getExpected() == Function::ArgName) {
            _setArgNameFunction(token);
        } else if (_functions.back().getExpected() == Function::EndArgs) {
            _setEndArgsFunction(token);
        } else if (_functions.back().getExpected() == Function::ReturnTypeOperator) {
            _setReturnTypeOperatorFunction(token);
        } else if (_functions.back().getExpected() == Function::ReturnType) {
            _setReturnTypeFunction(token);
        } else if (_functions.back().getExpected() == Function::StartBlock) {
            _setStartBlockFunction(token);
        } else if (_functions.back().getExpected() == Function::Block) {
            _setBlockFunction(token);
        }
    }

    void Parser::_lineSyntacticAnalysis(const token_line_t &line) {
        for (const token_t &token : line.second) {
            if (Error::getTypeError() == Error::None) {
                _tokenSyntacticAnalysis(token);
            } else {
                Error::setTextError(std::format(L"Syntax error in the line: {}", line.first));
            }
        }
    }

    void Parser::_syntacticAnalysis() {
        for (const token_line_t &line : _token_list) {
            if (!line.second.empty()) {
                if (Error::getTypeError() == Error::None) {
                    _lineSyntacticAnalysis(line);
                }
            }
        }
    }

    Parser::Parser(const std::string &file_name) : Lexer(file_name) {
        moveTokenList(_token_list);
        _syntacticAnalysis();
    }

    Parser::Parser(const token_list_t &token_list) : _token_list(token_list) {}

    Parser::Parser(token_list_t &&token_list) : _token_list(std::move(token_list)) {}
}  // namespace crc
