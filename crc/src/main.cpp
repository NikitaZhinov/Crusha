#include "../include/args-parser/args-parser.h"

int main(int argc, const char** argv) {
    crc::ArgsParser args_parser(argc, argv);
    args_parser.runOptions();

    crc::Error::printError();
    return crc::Error::getTypeError();
}
