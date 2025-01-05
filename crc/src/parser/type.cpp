#include "../../include/parser/type.h"

namespace crc {
    const std::vector<std::pair<std::wstring, Type::TypeId>> Type::_TYPES = {
        std::pair<std::wstring, Type::TypeId>(L"int", Int),     std::pair<std::wstring, Type::TypeId>(L"ufloat", UFloat),
        std::pair<std::wstring, Type::TypeId>(L"uint", UInt),   std::pair<std::wstring, Type::TypeId>(L"char", Char),
        std::pair<std::wstring, Type::TypeId>(L"float", Float),
    };

    std::vector<std::pair<std::wstring, Type::TypeId>> Type::getTypes() {
        return _TYPES;
    }

    Type::TypeId Type::getTypeId(const std::wstring &name) {
        for (const auto &pair_type : _TYPES) {
            if (pair_type.first == name) {
                return pair_type.second;
            }
        }
        return Void;
    }
}  // namespace crc
