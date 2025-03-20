#pragma once

#include <args-parser/args-parser.h>

namespace crc {
    namespace option {
        /**
         * @brief The class for compiling files.
         */
        class Default : public args::IOption {
        public:
            /**
             * @brief Accepts the file name and compiles it.
             *
             * @return int
             */
            int call(const char** args) const override;
        };

        /**
         * @brief The class for getting the current version.
         */
        class Version : public args::IOption {
        public:
            /**
             * @brief Sets name as "--version".
             */
            Version();

            /**
             * @brief Outputs the current version of the compiler to the stdout.
             *
             * @return int
             */
            int call(const char** args) const override;
        };
    }  // namespace option
}  // namespace crc
