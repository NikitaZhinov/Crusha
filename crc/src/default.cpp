#include <option/default.h>

#include <compiler/compiler.h>

#include <print>

void crc::option::Default::call(const char** args) const {
    Compiler compiler;
    auto compile_result = compiler.compile(args[0]);
    if (compile_result) {
        std::println(compile_result.value());
    }
}
