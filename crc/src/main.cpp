#include <option/option.h>

#include <print>

int main(int argc, const char** argv) {
    args::ArgsParser args_parser(argc, argv);

    crc::option::Default default_option;
    crc::option::Version version_option;

    args_parser.addOption(&default_option);
    args_parser.addOption(&version_option);

    return args_parser.callOptions();
}
