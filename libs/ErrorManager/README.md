# ErrorManager
A library for tracking errors.

## About
The library detects a list of errors and stops the program if an error occurs.

## Usage
An ErrorManager class object is created, to which error texts are added in order. By default, ErrorManager has an error with code 0, which can be set to text when creating an object. After that, a function is launched via ErrorManager that may cause an error.

## Example
main.cpp
```
#include <iostream>
#include <error-manager/error-manager.h>

static void good(error::ErrorManager& error_manager) {}

static void syntax(error::ErrorManager& error_manager) {
    error_manager.callError(1, "syntax error");
}

static void compile(error::ErrorManager& error_manager) {
    error_manager.callError(2, "compile error");
}

int main() {
    error::ErrorManager error_manager("All good");

    error_manager.addError("Syntax:"); // id = 1
    error_manager.addError("Compile:"); // id = 2
    error_manager.addError("Link:"); // id = 3

    std::string message;

    int err = error_manager.start(message, syntax);
    std::cout << message << std::endl;

    return err;
}
```
CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 3.20)

project(MyApp)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ErrorManager)
```
Run:
```bash
./MyApp
```
Output:
```
Syntax: syntax error
```