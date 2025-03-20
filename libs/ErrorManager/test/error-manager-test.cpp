#include "../include/error-manager/error-manager.h"

#include <gtest/gtest.h>

static void good(error::ErrorManager& error_manager) {}

static void syntax(error::ErrorManager& error_manager) {
    error_manager.callError(1, "syntax error");
}

static void compile(error::ErrorManager& error_manager) {
    error_manager.callError(2, "compile error");
}

TEST(ErrorManagerTest, Test_0) {
    error::ErrorManager error_manager("All good");

    error_manager.addError("syntax");
    error_manager.addError("compile");
    error_manager.addError("link");

    std::string message;

    ASSERT_EQ(error_manager.start(message, good), 0);
    ASSERT_EQ(message, std::string("All good"));
}

TEST(ErrorManagerTest, Test_1) {
    error::ErrorManager error_manager("All good");

    error_manager.addError("syntax");
    error_manager.addError("compile");
    error_manager.addError("link");

    std::string message;

    ASSERT_EQ(error_manager.start(message, syntax), 1);
    ASSERT_EQ(message, std::string("syntax syntax error"));
}

TEST(ErrorManagerTest, Test_2) {
    error::ErrorManager error_manager("All good");

    error_manager.addError("syntax");
    error_manager.addError("compile");
    error_manager.addError("link");

    std::string message;

    ASSERT_EQ(error_manager.start(message, compile), 2);
    ASSERT_EQ(message, std::string("compile compile error"));
}
