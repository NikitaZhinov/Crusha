#pragma once

#include <string>
#include <vector>

namespace crc {
    class Dictionary {
        static const std::vector<std::wstring> _KEY_WORDS;

    public:
        static std::vector<std::wstring> getKeyWords();

        static bool isNameExist(const std::wstring &name);
    };
}
