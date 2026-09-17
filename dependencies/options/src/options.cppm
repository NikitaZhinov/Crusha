module;

#include <string_view>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <sstream>
#include <memory>

export module options;

namespace options {
    struct Option final {
        bool exist = false;
        bool has_value;
        std::string value;

        constexpr explicit Option(bool has_value_) : has_value(has_value_) {}
    };

    /**
     * @brief Enumerate of all monitored errors when entering options.
     */
    export enum Error {
        Ok,
        EmptyOption,
        EmptyValue,
        UndefinedOption,
        ExtraValue
    };

    /**
     * @brief Detects an error when entering options.
     */
    export struct ErrorPos final {
        /**
         * @brief Error code.
         */
        Error error = Ok;

        /**
         * @brief The number of the option with the error.
         */
        int pos = -1;
    };

    /**
     * Option parser class.
     */
    export class OptionsParser final {
        using option_t = std::shared_ptr<Option>;
        using options_names_contaner_t = std::unordered_map<std::string, option_t>;

        options_names_contaner_t options_names_;
        options_names_contaner_t options_short_names_;

        bool is_parsed_ = false;

        void check(const std::string_view& name) const {
            if (!is_parsed_) {
                throw std::logic_error("arguments must be parsed before query options");
            }

            if (!options_names_.count(name.data())) {
                throw std::logic_error("option is not found");
            }
        }

    public:
        /**
         * @brief Adds new option.
         *
         * @param name A full option name. For a call, put a '--' before the name.
         * @param short_name Abbreviated name. For a call, put a '-' before the name. The
         * default value is an empty value.
         * @param has_value Should the option take the value. By default, it is true.
         */
        void addOption(const std::string_view& name, const std::string_view& short_name = "",
                       bool has_value = true) {
            auto opt_ptr = std::make_shared<Option>(has_value);

            options_names_.emplace(name, opt_ptr);

            if (!short_name.empty()) {
                options_short_names_.emplace(short_name, opt_ptr);
            }
        }

        /**
         * @brief Parses incoming options. Returns the position and error code, if there
         * are no errors: code is Ok, position is -1.
         *
         * @param argc Number of options.
         * @param argv Array of options.
         *
         * @return ErrorPos
         */
        ErrorPos parse(int argc, const char* argv[]) {
            for (int i = 1; i < argc; ++i) {
                if (argv[i][0] == '-') {
                    std::string_view arg = argv[i];

                    arg.remove_prefix(1);

                    if (arg.empty()) {
                        return ErrorPos { EmptyOption, i };
                    }

                    std::string opt, val;

                    auto trim_pos = arg.find_first_of('=');

                    if (trim_pos == std::string::npos) {
                        opt = std::move(arg);

                        if (i + 1 < argc) {
                            val = argv[i + 1];
                            if (val.front() == '-') {
                                return ErrorPos { EmptyValue, i };
                            }
                            ++i;
                        }
                    } else {
                        opt = arg.substr(0, trim_pos);
                        val = arg.substr(trim_pos + 1);
                    }

                    option_t opt_it;

                    if (opt[0] == '-') {
                        opt.erase(opt.begin());

                        if (!options_names_.count(opt)) {
                            return ErrorPos { UndefinedOption, i };
                        }

                        opt_it = options_names_[opt];
                    } else {
                        if (!options_short_names_.count(opt)) {
                            return ErrorPos { UndefinedOption, i };
                        }

                        opt_it = options_short_names_[opt];
                    }

                    opt_it->exist = true;

                    if (opt_it->has_value) {
                        if (val.empty()) {
                            return ErrorPos { EmptyValue, i };
                        }

                        opt_it->value = std::move(val);
                    } else if (trim_pos != std::string::npos) {
                        return ErrorPos { ExtraValue, i };
                    }
                }
            }

            is_parsed_ = true;

            return ErrorPos { Ok, -1 };
        }

        /**
         * @brief Checks whether the option has been entered. Applies to all options. It
         * is used only after parsing incoming options.
         *
         * @param name Full name of the option.
         *
         * @throw std::logic_error
         *
         * @return bool
         */
        bool isExist(const std::string_view& name) const {
            check(name);

            return options_names_.find(name.data())->second->exist;
        }

        /**
         * @brief Gets the value of the option. Applies to options that have the
         * has_value=true parameter when added. It is used only after parsing incoming
         * options.
         *
         * @tparam T Type of the returned parameter.
         *
         * @param name Full name of the option.
         *
         * @throw std::logic_error
         *
         * @return T
         */
        template <class T> T get(const std::string_view& name) const {
            check(name);

            const auto& str_value = options_names_.find(name.data())->second->value;

            std::istringstream is { str_value };

            T value {};

            is >> value;

            return value;
        }

        /**
         * @brief Checks whether incoming options have been parsed.
         *
         * @return bool
         */
        bool isParsed() const noexcept {
            return is_parsed_;
        }
    };
}  // namespace options
