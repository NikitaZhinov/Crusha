#pragma once

#include "option.h"

#include <list>

namespace args {
    /**
     * @brief The main class for manipulating command line arguments.
     */
    class ArgsParser {
        int _argc;
        const char** _argv;

        std::list<IOption*> _option_list;

        bool _default_option_exist;

    public:
        /**
         * @brief Initialize the _argv = argc, _argv = argv, _default_option_exist = false field.
         */
        ArgsParser(int argc, const char** argv);

        /**
         * @brief Returns a list of options.
         * @return A list of options.
         */
        std::list<IOption*> getOptions() const;

        /**
         * @brief Adds an option to the list of options.
         * @param option - Pointer to an option.
         */
        void addOption(IOption* option);

        /**
         * @brief Calls the options found in argv.
         */
        int callOptions();
    };
}  // namespace args
