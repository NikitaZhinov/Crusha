# ArgsParser
A library for manipulating command line arguments.

## About
The library makes it convenient to work with command-line arguments and easily extend your application.

## Usage
An ArgsParser class object is created, to which argc and argv are passed. Then pointers are added to objects of classes inherited from the abstract class IOption. If an option has no name specified, it is considered the default option and is called if there are no matches with other options of the current argument.

## Example
main.cpp:
```cpp
#include <iostream>
#include <args-parser/args-parser.h>

class VersionOption : public args::IOption {
public:
  VersionOption() { this->setName("--version"); }

  void call(const char** args) const override { std::cout << "Your application version: 1.0.0" << std::endl; }
};

class DefaultOption : public args::IOption {
public:
  void call(const char** args) const override { std::cout << "Hello " << args[0] << std::endl; }
};

int main(int argc, const char** argv) {
  // create ArgsParser object
  args::ArgsParser args_parser(argc, argv);

  // create options
  VersionOption version_option;

  // add options
  args_parser.addOption(&version_option);

  // call options
  args_parser.callOptions();
}
```
CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 3.20)

project(MyApp)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ArgsParser)
```
Run:
```bash
./MyApp --version World
```
Output:
```
Your application version: 1.0.0
Hello World
```
