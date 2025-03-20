#include <option/option.h>

#include <compiler/compiler.h>

#include <print>

int crc::option::Default::call(const char** args) const {
    error::ErrorManager error_manager("Compile succses");
    error_manager.addError("Compile failed:");
    std::string error_message;
    std::uint64_t error_code = error_manager.start(error_message, compile, args[0]);
    std::println("{}", error_message);

    return error_code;
}

crc::option::Version::Version() {
    this->setName("--version");
}

int crc::option::Version::call(const char** args) const {
    std::println("CRC (CR Compiler) version: {}", CRC_VERSION);
    return 0;
}
