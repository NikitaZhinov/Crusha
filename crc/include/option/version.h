#pragma once

#include <args-parser/args-parser.h>

namespace crc {
    namespace option {
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
            void call(const char** args) const override;
        };
    }
}
