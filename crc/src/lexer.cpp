#include "lexer.hpp"

#include <iostream>
#include <print>
#include <stdexcept>

void Lexer::nextRow() noexcept {
    ++row_;
    col_ = 1;
}

void Lexer::nextCol(std::size_t step) noexcept {
    col_ += step;
}

void Lexer::processUnknow() {
    throw std::runtime_error("unknow token");
}

#ifndef LEXER_PRINT_TOKENS_

int Lexer::processLiteralInt(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::LITERAL_INT;
}

int Lexer::processLiteralFloat(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::LITERAL_FLOAT;
}

int Lexer::processLiteralString(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::LITERAL_STRING;
}

int Lexer::processLiteralChar(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::LITERAL_CHAR;
}

int Lexer::processComment(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::COMMENT;
}

int Lexer::processCommentBlock(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::COMMENT_BLOCK;
}

int Lexer::processKWFunc(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::KW_FUNC;
}

int Lexer::processKWLet(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::KW_LET;
}

int Lexer::processKWReturn(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::KW_RETURN;
}

int Lexer::processKWNew(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::KW_NEW;
}

int Lexer::processKWClass(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::KW_CLASS;
}

int Lexer::processColon(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::COLON;
}

int Lexer::processLeftArrow(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::LEFT_ARROW;
}

int Lexer::processPlus(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::PLUS;
}

int Lexer::processMinus(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::MINUS;
}

int Lexer::processMultiplication(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::MULTIPLICATION;
}

int Lexer::processDivision(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::DIVISION;
}

int Lexer::processAssignment(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::ASSIGNMENT;
}

int Lexer::processLP(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::LP;
}

int Lexer::processRP(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::RP;
}

int Lexer::processLB(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::LB;
}

int Lexer::processRB(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::RB;
}

int Lexer::processComma(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::COMMA;
}

int Lexer::processScolon(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::SCOLON;
}

int Lexer::processName(std::size_t step) noexcept {
    nextCol(step);
    return yy::parser::token_type::NAME;
}

#else

void Lexer::print(const std::string_view& token) {
    std::println("{}:{}\t{}\t- {}", row_, col_, yytext, token);
}

int Lexer::processLiteralInt(std::size_t step) {
    nextCol(step);
    print("LITERAL_INT");
    return yy::parser::token_type::LITERAL_INT;
}

int Lexer::processLiteralFloat(std::size_t step) {
    nextCol(step);
    print("LITERAL_FLOAT");
    return yy::parser::token_type::LITERAL_FLOAT;
}

int Lexer::processLiteralString(std::size_t step) {
    nextCol(step);
    print("LITERAL_STRING");
    return yy::parser::token_type::LITERAL_STRING;
}

int Lexer::processLiteralChar(std::size_t step) {
    nextCol(step);
    print("LITERAL_CHAR");
    return yy::parser::token_type::LITERAL_CHAR;
}

int Lexer::processComment(std::size_t step) {
    nextCol(step);
    print("COMMENT");
    return yy::parser::token_type::COMMENT;
}

int Lexer::processCommentBlock(std::size_t step) {
    nextCol(step);
    print("COMMENT_BLOCK");
    return yy::parser::token_type::COMMENT_BLOCK;
}

int Lexer::processKWFunc(std::size_t step) {
    nextCol(step);
    print("KW_FUNC");
    return yy::parser::token_type::KW_FUNC;
}

int Lexer::processKWLet(std::size_t step) {
    nextCol(step);
    print("KW_LET");
    return yy::parser::token_type::KW_LET;
}

int Lexer::processKWReturn(std::size_t step) {
    nextCol(step);
    print("KW_RETURN");
    return yy::parser::token_type::KW_RETURN;
}

int Lexer::processKWNew(std::size_t step) {
    nextCol(step);
    print("KW_NEW");
    return yy::parser::token_type::KW_NEW;
}

int Lexer::processKWClass(std::size_t step) {
    nextCol(step);
    print("KW_CLASS");
    return yy::parser::token_type::KW_CLASS;
}


int Lexer::processColon(std::size_t step) {
    nextCol(step);
    print("COLON");
    return yy::parser::token_type::COLON;
}

int Lexer::processLeftArrow(std::size_t step) {
    nextCol(step);
    print("LEFT_ARROW");
    return yy::parser::token_type::LEFT_ARROW;
}

int Lexer::processPlus(std::size_t step) {
    nextCol(step);
    print("PLUS");
    return yy::parser::token_type::PLUS;
}

int Lexer::processMinus(std::size_t step) {
    nextCol(step);
    print("MINUS");
    return yy::parser::token_type::MINUS;
}

int Lexer::processMultiplication(std::size_t step) {
    nextCol(step);
    print("MULTIPLICATION");
    return yy::parser::token_type::MULTIPLICATION;
}

int Lexer::processDivision(std::size_t step) {
    nextCol(step);
    print("DIVISION");
    return yy::parser::token_type::DIVISION;
}

int Lexer::processAssignment(std::size_t step) {
    nextCol(step);
    print("ASSIGNMENT");
    return yy::parser::token_type::ASSIGNMENT;
}

int Lexer::processLP(std::size_t step) {
    nextCol(step);
    print("LP");
    return yy::parser::token_type::LP;
}

int Lexer::processRP(std::size_t step) {
    nextCol(step);
    print("RP");
    return yy::parser::token_type::RP;
}

int Lexer::processLB(std::size_t step) {
    nextCol(step);
    print("LB");
    return yy::parser::token_type::LB;
}

int Lexer::processRB(std::size_t step) {
    nextCol(step);
    print("RB");
    return yy::parser::token_type::RB;
}

int Lexer::processComma(std::size_t step) {
    nextCol(step);
    print("COMMA");
    return yy::parser::token_type::COMMA;
}

int Lexer::processScolon(std::size_t step) {
    nextCol(step);
    print("SCOLON");
    return yy::parser::token_type::SCOLON;
}

int Lexer::processName(std::size_t step) {
    nextCol(step);
    print("NAME");
    return yy::parser::token_type::NAME;
}

#endif

Lexer::Lexer(std::istream& is) : yyFlexLexer(is, std::cout) {}
