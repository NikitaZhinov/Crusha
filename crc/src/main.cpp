#include <option/option.h>

#include <print>

int main(int argc, const char** argv) {
    args::ArgsParser args_parser(argc, argv);

    args_parser.addOption<crc::option::Default>();
    args_parser.addOption<crc::option::Version>();

    args_parser.callOptions();

    return 0;
}
