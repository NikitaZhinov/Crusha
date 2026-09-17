#include <gtest/gtest.h>
#include <stdexcept>

import options;

TEST(OptionsTest, SuccessTest) {
    options::OptionsParser op;

    op.addOption("a");
    op.addOption("b", "b");
    op.addOption("cc", "c");
    op.addOption("ddd", "d", false);

    constexpr int argc = 5;
    const char* argv[argc] { "test.exe", "--a=1", "-b=2", "-c=3", "--ddd" };

    auto res = op.parse(argc, argv);

    EXPECT_EQ(res.error, options::Ok);
    EXPECT_EQ(res.pos, -1);
    EXPECT_EQ(op.template get<int>("a"), 1);
    EXPECT_EQ(op.template get<int>("b"), 2);
    EXPECT_EQ(op.template get<int>("cc"), 3);
    EXPECT_TRUE(op.isExist("ddd"));
}

TEST(OptionsTest, EmptyOptionTest) {
    options::OptionsParser op;

    op.addOption("a");
    op.addOption("b", "b");
    op.addOption("cc", "c");
    op.addOption("ddd", "d", false);

    constexpr int argc = 5;
    const char* argv[argc] { "test.exe", "--a=1", "-", "-c=3", "--ddd" };

    auto res = op.parse(argc, argv);

    EXPECT_EQ(res.error, options::EmptyOption);
    EXPECT_EQ(res.pos, 2);
    EXPECT_THROW(op.template get<int>("a"), std::logic_error);
    EXPECT_THROW(op.isExist("ddd"), std::logic_error);
}

TEST(OptionsTest, EmptyValue1Test) {
    options::OptionsParser op;

    op.addOption("a");
    op.addOption("b", "b");
    op.addOption("cc", "c");
    op.addOption("ddd", "d", false);

    constexpr int argc = 5;
    const char* argv[argc] { "test.exe", "--a=1", "-b", "-c=3", "--ddd" };

    auto res = op.parse(argc, argv);

    EXPECT_EQ(res.error, options::EmptyValue);
    EXPECT_EQ(res.pos, 2);
    EXPECT_THROW(op.template get<int>("a"), std::logic_error);
    EXPECT_THROW(op.isExist("ddd"), std::logic_error);
}

TEST(OptionsTest, EmptyValue2Test) {
    options::OptionsParser op;

    op.addOption("a");
    op.addOption("b", "b");
    op.addOption("cc", "c");
    op.addOption("ddd", "d", false);

    constexpr int argc = 5;
    const char* argv[argc] { "test.exe", "--a=1", "-b=", "-c=3", "--ddd" };

    auto res = op.parse(argc, argv);

    EXPECT_EQ(res.error, options::EmptyValue);
    EXPECT_EQ(res.pos, 2);
    EXPECT_THROW(op.template get<int>("a"), std::logic_error);
    EXPECT_THROW(op.isExist("ddd"), std::logic_error);
}

TEST(OptionsTest, UndefinedOptionTest) {
    options::OptionsParser op;

    op.addOption("a");
    op.addOption("b", "b");
    op.addOption("cc", "c");
    op.addOption("ddd", "d", false);

    constexpr int argc = 5;
    const char* argv[argc] { "test.exe", "--a=1", "asdsa", "-c=3", "--ddd" };

    auto res = op.parse(argc, argv);

    EXPECT_EQ(res.error, options::UndefinedOption);
    EXPECT_EQ(res.pos, 2);
    EXPECT_THROW(op.template get<int>("a"), std::logic_error);
    EXPECT_THROW(op.isExist("ddd"), std::logic_error);
}

TEST(OptionsTest, ExtraValueTest) {
    options::OptionsParser op;

    op.addOption("a");
    op.addOption("b", "b");
    op.addOption("cc", "c");
    op.addOption("ddd", "d", false);

    constexpr int argc = 5;
    const char* argv[argc] { "test.exe", "--a=1", "-b=2", "-c=3", "--ddd=333" };

    auto res = op.parse(argc, argv);

    EXPECT_EQ(res.error, options::ExtraValue);
    EXPECT_EQ(res.pos, 4);
    EXPECT_THROW(op.template get<int>("a"), std::logic_error);
    EXPECT_THROW(op.isExist("ddd"), std::logic_error);
}
