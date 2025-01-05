#pragma once

#include <string>
#include <vector>

namespace crc {
    class Type {
    public:
        enum TypeId {
            Void = 0,
            Int,
            UInt,
            Float,
            UFloat,
            Char,
        };

    private:
        static const std::vector<std::pair<std::wstring, TypeId>> _TYPES;

    public:
        static std::vector<std::pair<std::wstring, TypeId>> getTypes();

        static Type::TypeId getTypeId(const std::wstring &name);
    };
}  // namespace crc
