#pragma once

#include <string_view>

#ifndef yyFlexLexer
    #include <FlexLexer.h>
#endif

#include "crc.tab.hh"

class Lexer final : public yyFlexLexer {
    std::size_t row_ = 1, col_ = 1;

    void nextRow() noexcept;
    void nextCol(std::size_t step = 1) noexcept;

    void processUnknow();

#ifndef LEXER_PRINT_TOKENS_
    int processLiteralInt(std::size_t step) noexcept;
    int processLiteralFloat(std::size_t step) noexcept;
    int processLiteralString(std::size_t step) noexcept;
    int processLiteralChar(std::size_t step) noexcept;

    int processComment(std::size_t step) noexcept;
    int processCommentBlock(std::size_t step) noexcept;

    int processKWFunc(std::size_t step) noexcept;
    int processKWLet(std::size_t step) noexcept;
    int processKWReturn(std::size_t step) noexcept;
    int processKWNew(std::size_t step) noexcept;
    int processKWClass(std::size_t step) noexcept;

    int processColon(std::size_t step) noexcept;
    int processLeftArrow(std::size_t step) noexcept;

    int processPlus(std::size_t step) noexcept;
    int processMinus(std::size_t step) noexcept;
    int processMultiplication(std::size_t step) noexcept;
    int processDivision(std::size_t step) noexcept;
    int processAssignment(std::size_t step) noexcept;

    int processLP(std::size_t step) noexcept;
    int processRP(std::size_t step) noexcept;
    int processLB(std::size_t step) noexcept;
    int processRB(std::size_t step) noexcept;

    int processComma(std::size_t step) noexcept;
    int processScolon(std::size_t step) noexcept;

    int processName(std::size_t step) noexcept;
#else
    void print(const std::string_view& token);

    int processLiteralInt(std::size_t step);
    int processLiteralFloat(std::size_t step);
    int processLiteralString(std::size_t step);
    int processLiteralChar(std::size_t step);

    int processComment(std::size_t step);
    int processCommentBlock(std::size_t step);

    int processKWFunc(std::size_t step);
    int processKWLet(std::size_t step);
    int processKWReturn(std::size_t step);
    int processKWNew(std::size_t step);
    int processKWClass(std::size_t step);

    int processColon(std::size_t step);
    int processLeftArrow(std::size_t step);

    int processPlus(std::size_t step);
    int processMinus(std::size_t step);
    int processMultiplication(std::size_t step);
    int processDivision(std::size_t step);
    int processAssignment(std::size_t step);

    int processLP(std::size_t step);
    int processRP(std::size_t step);
    int processLB(std::size_t step);
    int processRB(std::size_t step);

    int processComma(std::size_t step);
    int processScolon(std::size_t step);

    int processName(std::size_t step);
#endif

public:
    Lexer(std::istream& is);

    int yylex() override;
};
