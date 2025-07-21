#include <option/version.h>

crc::option::Version::Version() {
    this->setName("--version");
}

void crc::option::Version::call(const char** args) const {
    std::println("CRC (Crusha Compiler) version: {}", CRC_VERSION);
}
