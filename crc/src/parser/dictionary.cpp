#include "../../include/parser/dictionary.h"

namespace crc {
    const std::vector<std::wstring> Dictionary::_KEY_WORDS = {
        L"char", L"float", L"func", L"int", L"return", L"ufloat", L"uint", L"var",
    };

    std::vector<std::wstring> Dictionary::getKeyWords() {
        return _KEY_WORDS;
    }

    bool Dictionary::isNameExist(const std::wstring &name) {
        return *std::lower_bound(_KEY_WORDS.begin(), _KEY_WORDS.end(), name) == name;
    }
}  // namespace crc
