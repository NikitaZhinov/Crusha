#include "../include/args-parser/args-parser.h"

#include <gtest/gtest.h>
#include <format>

class Program {
    static std::string text;
    static std::string version;
    static std::string output;

public:
    static void restart() {
        text = "";
        version = "";
        output = "";
    }

    static void setText(const std::string& str) {
        text = str;
    }

    static std::string getText() {
        return text;
    }

    static void setVersion(const std::string& ver) {
        version = ver;
    }

    static std::string getVersion() {
        return version;
    }

    static void print(const std::string& out) {
        output = out;
    }

    static std::string getPrint() {
        return output;
    }
};

std::string Program::text;
std::string Program::version;
std::string Program::output;

class DefaultOption : public args::IOption {
public:
    int call(const char** args) const override {
        Program::setText(std::format("call: {}", args[0]));
        return 0;
    }
};

class VersionOption : public args::IOption {
public:
    VersionOption() {
        this->setName("--version");
    }

    int call(const char** args) const override {
        Program::setVersion("version: 1.0.0");
        return 0;
    }
};

class PrintOption : public args::IOption {
public:
    PrintOption() {
        this->setName("--print");
    }

    int call(const char** args) const override {
        Program::print("Hello, World!");
        return 0;
    }
};

TEST(ArgsParserOptionTest, OptionTest_0) {
    int argc = 2;
    const char* argv[] = { "test.exe", "--version" };
    Program::restart();

    args::ArgsParser args_parser(argc, argv);

    VersionOption version_option;

    args_parser.addOption(&version_option);
    args_parser.callOptions();

    ASSERT_EQ("version: 1.0.0", Program::getVersion());
}

TEST(ArgsParserOptionTest, OptionTest_1) {
    int argc = 3;
    const char* argv[] = { "test.exe", "--version", "--print" };
    Program::restart();

    args::ArgsParser args_parser(argc, argv);

    VersionOption version_option;
    PrintOption print_option;

    args_parser.addOption(&version_option);
    args_parser.addOption(&print_option);
    args_parser.callOptions();

    ASSERT_EQ("version: 1.0.0", Program::getVersion());
    ASSERT_EQ("Hello, World!", Program::getPrint());
}

TEST(ArgsParserDefaltOptionTest, DefaltOptionTest_0) {
    int argc = 2;
    const char* argv[] = { "test.exe", "someoption" };
    Program::restart();

    args::ArgsParser args_parser(argc, argv);

    DefaultOption default_option;

    args_parser.addOption(&default_option);
    args_parser.callOptions();

    ASSERT_EQ("call: someoption", Program::getText());
}

TEST(ArgsParserDefaltOptionTest, DefaltOptionTest_1) {
    int argc = 3;
    const char* argv[] = { "test.exe", "--version", "someoption" };
    Program::restart();

    args::ArgsParser args_parser(argc, argv);

    DefaultOption default_option;
    VersionOption version_option;

    args_parser.addOption(&default_option);
    args_parser.addOption(&version_option);
    args_parser.callOptions();

    ASSERT_EQ("call: someoption", Program::getText());
    ASSERT_EQ("version: 1.0.0", Program::getVersion());
}

TEST(ArgsParserDefaltOptionTest, DefaltOptionTest_2) {
    int argc = 4;
    const char* argv[] = { "test.exe", "--version", "someoption", "--print" };
    Program::restart();

    args::ArgsParser args_parser(argc, argv);

    DefaultOption default_option;
    VersionOption version_option;
    PrintOption print_option;

    args_parser.addOption(&default_option);
    args_parser.addOption(&version_option);
    args_parser.addOption(&print_option);
    args_parser.callOptions();

    ASSERT_EQ("call: someoption", Program::getText());
    ASSERT_EQ("version: 1.0.0", Program::getVersion());
    ASSERT_EQ("Hello, World!", Program::getPrint());
}
