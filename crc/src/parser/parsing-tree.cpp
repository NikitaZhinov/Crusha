#include "../../include/parser/parsing-tree.h"

namespace crc {
    ParsingTree::Node::Node(const std::wstring &func) : funciton(func) {}

    ParsingTree::ParsingTree(const std::wstring function) : _root(function) {}
}  // namespace crc
