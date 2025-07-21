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
            void call(const char** args) const override;
        };
    }  // namespace option
}  // namespace crc
